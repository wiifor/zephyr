/*
 * Copyright (c) 2019, Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT nxp_imx_csi

#include <zephyr.h>

#include <fsl_csi.h>

#ifdef CONFIG_HAS_MCUX_CACHE
#include <fsl_cache.h>
#endif

#include <drivers/video.h>

struct video_mcux_csi_config {
	CSI_Type *base;
	char *sensor_label;
};

struct video_mcux_csi_data {
	const struct device *dev;
	const struct device *sensor_dev;
	csi_config_t csi_config;
	csi_handle_t csi_handle;
	struct k_fifo fifo_in;
	struct k_fifo fifo_out;
	uint32_t pixelformat;
	struct k_poll_signal *signal;
};

static inline unsigned int video_pix_fmt_bpp(uint32_t pixelformat)
{
	switch (pixelformat) {
	case VIDEO_PIX_FMT_BGGR8:
	case VIDEO_PIX_FMT_GBRG8:
	case VIDEO_PIX_FMT_GRBG8:
	case VIDEO_PIX_FMT_RGGB8:
		return 1;
	case VIDEO_PIX_FMT_RGB565:
		return 2;
	default:
		return 0;
	}
}

static void __frame_done_cb(CSI_Type *base, csi_handle_t *handle,
			    status_t status, void *user_data)
{
	struct video_mcux_csi_data *data = user_data;
	const struct device *dev = data->dev;
	const struct video_mcux_csi_config *config = dev->config;
	enum video_signal_result result = VIDEO_BUF_DONE;
	struct video_buffer *vbuf, *vbuf_first = NULL;
	uint32_t buffer_addr;

	/* IRQ context */

	if (status != kStatus_CSI_FrameDone) {
		return;
	}

	status = CSI_TransferGetFullBuffer(config->base, &(data->csi_handle),
					   &buffer_addr);
	if (status != kStatus_Success) {
		result = VIDEO_BUF_ERROR;
		goto done;
	}

	/* Get matching vbuf by addr */
	while ((vbuf = k_fifo_get(&data->fifo_in, K_NO_WAIT))) {
		if ((uint32_t)vbuf->buffer == buffer_addr) {
			break;
		}

		/* should never happen on ordered stream, except on capture
		 * start/restart, requeue the frame and continue looking for
		 * the right buffer.
		 */
		k_fifo_put(&data->fifo_in, vbuf);

		/* prevent infinite loop */
		if (vbuf_first == NULL) {
			vbuf_first = vbuf;
		} else if (vbuf_first == vbuf) {
			vbuf = NULL;
			break;
		}
	}

	if (vbuf == NULL) {
		result = VIDEO_BUF_ERROR;
		goto done;
	}

	vbuf->timestamp = k_uptime_get_32();

#ifdef CONFIG_HAS_MCUX_CACHE
	DCACHE_InvalidateByRange(buffer_addr, vbuf->bytesused);
#endif

	k_fifo_put(&data->fifo_out, vbuf);

done:
	/* Trigger Event */
	if (IS_ENABLED(CONFIG_POLL) && data->signal) {
		k_poll_signal_raise(data->signal, result);
	}

	return;
}

static int video_mcux_csi_set_fmt(const struct device *dev,
				  enum video_endpoint_id ep,
				  struct video_format *fmt)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;
	unsigned int bpp = video_pix_fmt_bpp(fmt->pixelformat);
	status_t ret;

	if (!bpp || ep != VIDEO_EP_OUT) {
		return -EINVAL;
	}

	data->pixelformat = fmt->pixelformat;
	data->csi_config.bytesPerPixel = bpp;
	data->csi_config.linePitch_Bytes = fmt->pitch;
	data->csi_config.polarityFlags = kCSI_HsyncActiveHigh | kCSI_DataLatchOnRisingEdge;
	data->csi_config.workMode = kCSI_GatedClockMode; /* use VSYNC, HSYNC, and PIXCLK */
	data->csi_config.dataBus = kCSI_DataBus8Bit;
	data->csi_config.useExtVsync = true;
	data->csi_config.height = fmt->height;
	data->csi_config.width = fmt->width;

	ret = CSI_Init(config->base, &data->csi_config);
	if (ret != kStatus_Success) {
		return -EIO;
	}

	ret = CSI_TransferCreateHandle(config->base, &data->csi_handle,
				       __frame_done_cb, data);
	if (ret != kStatus_Success) {
		return -EIO;
	}

	if (data->sensor_dev && video_set_format(data->sensor_dev, ep, fmt)) {
		return -EIO;
	}

	return 0;
}

static int video_mcux_csi_get_fmt(const struct device *dev,
				  enum video_endpoint_id ep,
				  struct video_format *fmt)
{
	struct video_mcux_csi_data *data = dev->data;

	if (fmt == NULL || ep != VIDEO_EP_OUT) {
		return -EINVAL;
	}

	if (data->sensor_dev && !video_get_format(data->sensor_dev, ep, fmt)) {
		/* align CSI with sensor fmt */
		return video_mcux_csi_set_fmt(dev, ep, fmt);
	}

	fmt->pixelformat = data->pixelformat;
	fmt->height = data->csi_config.height;
	fmt->width = data->csi_config.width;
	fmt->pitch = data->csi_config.linePitch_Bytes;

	return 0;
}

static int video_mcux_csi_stream_start(const struct device *dev)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;
	status_t ret;

	ret = CSI_TransferStart(config->base, &data->csi_handle);
	if (ret != kStatus_Success) {
		return -EIO;
	}

	if (data->sensor_dev && video_stream_start(data->sensor_dev)) {
		return -EIO;
	}

	return 0;
}

static int video_mcux_csi_stream_stop(const struct device *dev)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;
	status_t ret;

	if (data->sensor_dev && video_stream_stop(data->sensor_dev)) {
		return -EIO;
	}

	ret = CSI_TransferStop(config->base, &data->csi_handle);
	if (ret != kStatus_Success) {
		return -EIO;
	}

	return 0;
}


static int video_mcux_csi_flush(const struct device *dev,
				enum video_endpoint_id ep,
				bool cancel)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;
	struct video_buf *vbuf;
	uint32_t buffer_addr;
	status_t ret;

	if (!cancel) {
		/* wait for all buffer to be processed */
		do {
			k_sleep(K_MSEC(1));
		} while (!k_fifo_is_empty(&data->fifo_in));
	} else {
		/* Flush driver ouput queue */
		do {
			ret = CSI_TransferGetFullBuffer(config->base,
							&(data->csi_handle),
							&buffer_addr);
		} while (ret == kStatus_Success);

		while ((vbuf = k_fifo_get(&data->fifo_in, K_NO_WAIT))) {
			k_fifo_put(&data->fifo_out, vbuf);
			if (IS_ENABLED(CONFIG_POLL) && data->signal) {
				k_poll_signal_raise(data->signal,
						    VIDEO_BUF_ABORTED);
			}
		}
	}

	return 0;
}

static int video_mcux_csi_enqueue(const struct device *dev,
				  enum video_endpoint_id ep,
				  struct video_buffer *vbuf)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;
	unsigned int to_read;
	status_t ret;

	if (ep != VIDEO_EP_OUT) {
		return -EINVAL;
	}

	to_read = data->csi_config.linePitch_Bytes * data->csi_config.height;
	vbuf->bytesused = to_read;

	ret = CSI_TransferSubmitEmptyBuffer(config->base, &data->csi_handle,
					    (uint32_t)vbuf->buffer);
	if (ret != kStatus_Success) {
		return -EIO;
	}

	k_fifo_put(&data->fifo_in, vbuf);

	return 0;
}

static int video_mcux_csi_dequeue(const struct device *dev,
				  enum video_endpoint_id ep,
				  struct video_buffer **vbuf,
				  k_timeout_t timeout)
{
	struct video_mcux_csi_data *data = dev->data;

	if (ep != VIDEO_EP_OUT) {
		return -EINVAL;
	}

	*vbuf = k_fifo_get(&data->fifo_out, timeout);
	if (*vbuf == NULL) {
		return -EAGAIN;
	}

	return 0;
}

static inline int video_mcux_csi_set_ctrl(const struct device *dev,
					  unsigned int cid,
					  void *value)
{
	struct video_mcux_csi_data *data = dev->data;
	int ret = -ENOTSUP;

	/* Forward to sensor dev if any */
	if (data->sensor_dev) {
		ret = video_set_ctrl(data->sensor_dev, cid, value);
	}

	return ret;
}

static inline int video_mcux_csi_get_ctrl(const struct device *dev,
					  unsigned int cid,
					  void *value)
{
	struct video_mcux_csi_data *data = dev->data;
	int ret = -ENOTSUP;

	/* Forward to sensor dev if any */
	if (data->sensor_dev) {
		ret = video_get_ctrl(data->sensor_dev, cid, value);
	}

	return ret;
}

static int video_mcux_csi_get_caps(const struct device *dev,
				   enum video_endpoint_id ep,
				   struct video_caps *caps)
{
	struct video_mcux_csi_data *data = dev->data;
	int err = -ENODEV;

	if (ep != VIDEO_EP_OUT) {
		return -EINVAL;
	}

	/* Just forward to sensor dev for now */
	if (data->sensor_dev) {
		err = video_get_caps(data->sensor_dev, ep, caps);
	}

	/* NXP MCUX CSI request at least 2 buffer before starting */
	caps->min_vbuf_count = 2;

	/* no sensor dev */
	return err;
}

extern void CSI_DriverIRQHandler(void);
static void video_mcux_csi_isr(const void *p)
{
	ARG_UNUSED(p);
	CSI_DriverIRQHandler();
}

static int video_mcux_csi_init(const struct device *dev)
{
	const struct video_mcux_csi_config *config = dev->config;
	struct video_mcux_csi_data *data = dev->data;

	k_fifo_init(&data->fifo_in);
	k_fifo_init(&data->fifo_out);

	CSI_GetDefaultConfig(&data->csi_config);

	/* check if there is any sensor device (video ctrl device) */
	if (config->sensor_label) {
		data->sensor_dev = device_get_binding(config->sensor_label);
		if (data->sensor_dev == NULL) {
			return -ENODEV;
		}
	}

	return 0;
}

#ifdef CONFIG_POLL
static int video_mcux_csi_set_signal(const struct device *dev,
				     enum video_endpoint_id ep,
				     struct k_poll_signal *signal)
{
	struct video_mcux_csi_data *data = dev->data;

	if (data->signal && signal != NULL) {
		return -EALREADY;
	}

	data->signal = signal;

	return 0;
}
#endif

static const struct video_driver_api video_mcux_csi_driver_api = {
	.set_format = video_mcux_csi_set_fmt,
	.get_format = video_mcux_csi_get_fmt,
	.stream_start = video_mcux_csi_stream_start,
	.stream_stop = video_mcux_csi_stream_stop,
	.flush = video_mcux_csi_flush,
	.enqueue = video_mcux_csi_enqueue,
	.dequeue = video_mcux_csi_dequeue,
	.set_ctrl = video_mcux_csi_set_ctrl,
	.get_ctrl = video_mcux_csi_get_ctrl,
	.get_caps = video_mcux_csi_get_caps,
#ifdef CONFIG_POLL
	.set_signal = video_mcux_csi_set_signal,
#endif
};

#if 1 /* Unique Instance */
static const struct video_mcux_csi_config video_mcux_csi_config_0 = {
	.base = (CSI_Type *)DT_INST_REG_ADDR(0),
	.sensor_label = DT_INST_PROP(0, sensor_label),
};

static struct video_mcux_csi_data video_mcux_csi_data_0;

static int video_mcux_csi_init_0(const struct device *dev)
{
	struct video_mcux_csi_data *data = dev->data;

	IRQ_CONNECT(DT_INST_IRQN(0), DT_INST_IRQ(0, priority),
		    video_mcux_csi_isr, NULL, 0);

	irq_enable(DT_INST_IRQN(0));

	data->dev = dev;

	return video_mcux_csi_init(dev);
}

DEVICE_DT_INST_DEFINE(0, &video_mcux_csi_init_0,
		    NULL, &video_mcux_csi_data_0,
		    &video_mcux_csi_config_0,
		    POST_KERNEL, CONFIG_VIDEO_INIT_PRIORITY,
		    &video_mcux_csi_driver_api);
#endif
