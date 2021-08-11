# Copyright (c) 2020 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

if [ -z "$RUNNING_FROM_MAIN_SCRIPT" ]; then
    echo "Do not run this script directly!"
    echo "Run $ZEPHYR_BASE/scripts/net/run-sample-tests.sh instead."
    exit 1
fi

start_configuration || return $?
start_zephyr "$overlay" || return $?

start_docker "/net-tools/echo-client -i eth0 192.0.2.1" \
		     "/net-tools/echo-client -i eth0 2001:db8::1" \
		     "/net-tools/echo-client -i eth0 192.0.2.1 -t" \
		     "/net-tools/echo-client -i eth0 2001:db8::1 -t"

wait_docker
result=$?

stop_zephyr
