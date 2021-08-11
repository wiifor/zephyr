/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_DECLARE(conn_mgr, CONFIG_NET_CONNECTION_MANAGER_LOG_LEVEL);

#include <errno.h>
#include <net/net_if.h>
#include <net/net_mgmt.h>

#include <conn_mgr.h>

extern uint16_t iface_states[CONN_MGR_IFACE_MAX];

static struct net_mgmt_event_callback iface_events_cb;
static struct net_mgmt_event_callback ipv6_events_cb;
static struct net_mgmt_event_callback ipv4_events_cb;

static void conn_mgr_iface_events_handler(struct net_mgmt_event_callback *cb,
					  uint32_t mgmt_event,
					  struct net_if *iface)
{
	int idx;

	NET_DBG("Iface event %u received on iface %d (%p)", mgmt_event,
		net_if_get_by_iface(iface), iface);

	if ((mgmt_event & CONN_MGR_IFACE_EVENTS_MASK) != mgmt_event) {
		return;
	}

	idx = net_if_get_by_iface(iface) - 1;

	NET_DBG("Iface index %u", idx);

	switch (NET_MGMT_GET_COMMAND(mgmt_event)) {
	case NET_EVENT_IF_CMD_DOWN:
		iface_states[idx] &= ~NET_STATE_IFACE_UP;
		break;
	case NET_EVENT_IF_CMD_UP:
		iface_states[idx] |= NET_STATE_IFACE_UP;
		break;
	default:
		return;
	}

	iface_states[idx] |= NET_STATE_CHANGED;
	k_sem_give(&conn_mgr_lock);
}

#if defined(CONFIG_NET_IPV6)
static void conn_mgr_ipv6_events_handler(struct net_mgmt_event_callback *cb,
					 uint32_t mgmt_event,
					 struct net_if *iface)
{
	int idx;

	NET_DBG("IPv6 event %u received on iface %d (%p)", mgmt_event,
		net_if_get_by_iface(iface), iface);

	if ((mgmt_event & CONN_MGR_IPV6_EVENTS_MASK) != mgmt_event) {
		return;
	}

	idx = net_if_get_by_iface(iface) - 1;

	NET_DBG("Iface index %u", idx);

	switch (NET_MGMT_GET_COMMAND(mgmt_event)) {
	case NET_EVENT_IPV6_CMD_ADDR_ADD:
		iface_states[idx] |= NET_STATE_IPV6_ADDR_SET;
		break;
	case NET_EVENT_IPV6_CMD_ADDR_DEL:
		if (net_if_ipv6_get_global_addr(NET_ADDR_PREFERRED, &iface)) {
			break;
		}

		iface_states[idx] &= ~NET_STATE_IPV6_ADDR_SET;
		break;
	case NET_EVENT_IPV6_CMD_DAD_SUCCEED:
		iface_states[idx] |= NET_STATE_IPV6_DAD_OK;
		break;
	case NET_EVENT_IPV6_CMD_DAD_FAILED:
		if (net_if_ipv6_get_global_addr(NET_ADDR_PREFERRED, &iface)) {
			break;
		}

		iface_states[idx] &= ~NET_STATE_IPV6_DAD_OK;
		break;
	default:
		return;
	}

	iface_states[idx] |= NET_STATE_CHANGED;
	k_sem_give(&conn_mgr_lock);
}
#else
static inline
void conn_mgr_ipv6_events_handler(struct net_mgmt_event_callback *cb,
				  uint32_t mgmt_event,
				  struct net_if *iface)
{
	ARG_UNUSED(cb);
	ARG_UNUSED(mgmt_event);
	ARG_UNUSED(iface);
}
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
static void conn_mgr_ipv4_events_handler(struct net_mgmt_event_callback *cb,
					 uint32_t mgmt_event,
					 struct net_if *iface)
{
	int idx;

	NET_DBG("IPv4 event %u received on iface %d (%p)", mgmt_event,
		net_if_get_by_iface(iface), iface);

	if ((mgmt_event & CONN_MGR_IPV4_EVENTS_MASK) != mgmt_event) {
		return;
	}

	idx = net_if_get_by_iface(iface) - 1;

	NET_DBG("Iface index %u", idx);

	switch (NET_MGMT_GET_COMMAND(mgmt_event)) {
	case NET_EVENT_IPV4_CMD_ADDR_ADD:
		iface_states[idx] |= NET_STATE_IPV4_ADDR_SET;
		break;
	case NET_EVENT_IPV4_CMD_ADDR_DEL:
		if (net_if_ipv4_get_global_addr(iface, NET_ADDR_PREFERRED)) {
			break;
		}

		iface_states[idx] &= ~NET_STATE_IPV4_ADDR_SET;
		break;
	default:
		return;
	}

	iface_states[idx] |= NET_STATE_CHANGED;
	k_sem_give(&conn_mgr_lock);
}
#else
static inline
void conn_mgr_ipv4_events_handler(struct net_mgmt_event_callback *cb,
				  uint32_t mgmt_event,
				  struct net_if *iface)
{
	ARG_UNUSED(cb);
	ARG_UNUSED(mgmt_event);
	ARG_UNUSED(iface);
}
#endif /* CONFIG_NET_IPV4 */

void conn_mgr_init_events_handler(void)
{
	net_mgmt_init_event_callback(&iface_events_cb,
				     conn_mgr_iface_events_handler,
				     CONN_MGR_IFACE_EVENTS_MASK);
	net_mgmt_add_event_callback(&iface_events_cb);

	if (IS_ENABLED(CONFIG_NET_IPV6)) {
		net_mgmt_init_event_callback(&ipv6_events_cb,
					     conn_mgr_ipv6_events_handler,
					     CONN_MGR_IPV6_EVENTS_MASK);
		net_mgmt_add_event_callback(&ipv6_events_cb);
	}

	if (IS_ENABLED(CONFIG_NET_IPV4)) {
		net_mgmt_init_event_callback(&ipv4_events_cb,
					     conn_mgr_ipv4_events_handler,
					     CONN_MGR_IPV4_EVENTS_MASK);
		net_mgmt_add_event_callback(&ipv4_events_cb);
	}
}
