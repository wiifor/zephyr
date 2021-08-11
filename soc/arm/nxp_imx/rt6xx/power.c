/*
 * Copyright (c) 2021, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <pm/pm.h>
#include "fsl_power.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(soc, CONFIG_SOC_LOG_LEVEL);

/*!< Power down all unnecessary blocks and enable RBB during deep sleep. */
#define APP_DEEPSLEEP_RUNCFG0 (SYSCTL0_PDRUNCFG0_LPOSC_PD_MASK | \
			SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK)
#define APP_DEEPSLEEP_RAM_APD 0xFFFFF8U
#define APP_DEEPSLEEP_RAM_PPD 0x0U
#define APP_EXCLUDE_FROM_DEEPSLEEP			\
	(((const uint32_t[]){APP_DEEPSLEEP_RUNCFG0, \
	(SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_APD_MASK | \
	 SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_PPD_MASK), \
	APP_DEEPSLEEP_RAM_APD, APP_DEEPSLEEP_RAM_PPD}))

/* Invoke Low Power/System Off specific Tasks */
void pm_power_state_set(struct pm_state_info info)
{
	/* FIXME: When this function is entered the Kernel has disabled
	 * interrupts using BASEPRI register. This is incorrect as it prevents
	 * waking up from any interrupt which priority is not 0. Work around the
	 * issue and disable interrupts using PRIMASK register as recommended
	 * by ARM.
	 */

	/* Set PRIMASK */
	__disable_irq();
	/* Set BASEPRI to 0 */
	irq_unlock(0);

	switch (info.state) {
	case PM_STATE_RUNTIME_IDLE:
		POWER_EnterSleep();
		break;
	case PM_STATE_SUSPEND_TO_IDLE:
		POWER_EnterDeepSleep(APP_EXCLUDE_FROM_DEEPSLEEP);
		break;
	default:
		LOG_DBG("Unsupported power state %u", info.state);
		break;
	}
}

/* Handle SOC specific activity after Low Power Mode Exit */
void pm_power_state_exit_post_ops(struct pm_state_info info)
{
	ARG_UNUSED(info);

	/* Clear PRIMASK */
	__enable_irq();
}
