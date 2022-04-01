/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

#define SLEEP_PERIOD_THREAD_MAIN_IN_MS 2000

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);

	while (1) {
		for ( int a = 100; a > 0; a-- )
		{
			printk("printk zztop\n");
			LOG_ERR("log");
		}

//		k_sleep(K_MSEC(1000));
		k_sleep(K_MSEC(SLEEP_PERIOD_THREAD_MAIN_IN_MS));
	}
}
