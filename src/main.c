/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

//#include <device.h>
#include <drivers/gpio.h>          // to provide GPIO_OUTPUT_ACTIVE, gpio_pin_set() and related

//#include <nrfxlib/nrf_modem/include/nrf_modem.h>
#include <nrf_modem.h>




// ---------------------------------------------------------------------
// - SECTION - defines
// ---------------------------------------------------------------------

#define SLEEP_PERIOD_THREAD_MAIN_IN_MS 30000


//
// Serial peripherals and high speed clocks are disabled, so configure
// an nRF9160DK LED as a sanity check that our firmware changes are in
// fact compiling and running on targeted board:
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Note 'led0' is a Device Tree Source (DTS) alias defined in file
// ncs/zephyr/boards/arm/nrf9160dk_nrf9160/nrf9160dk_nrf9160_common.dts

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#warning --- --- --- macro evaluating 'led0' dts alias returns true --- --- ---
#define LED0_LABEL   DT_GPIO_LABEL(LED0_NODE, gpios)
#define LED0_PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define LED0_FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
#warning --- --- --- macro evaluating 'led0' dts alias returns false --- --- ---
#define LED0_LABEL   ""
#define LED0_PIN     0
#define LED0_FLAGS   0
#endif



// ---------------------------------------------------------------------
// - SECTION - file scoped
// ---------------------------------------------------------------------

enum zephyr_test_low_power_return_values
{
    ROUTINE_OK = 0,
    ZR__WARNING__FAIL_ON_DEVICE_GET_BINDING,
    ZR__WARNING__FAIL_ON_GPIO_PIN_CONFIGURE
};

static const struct device *dev_led0_green;



// ---------------------------------------------------------------------
// - SECTION - routines
// ---------------------------------------------------------------------

static uint32_t app_config__configure_line__led0(void)
{
    uint32_t rstatus = ROUTINE_OK;

    dev_led0_green = device_get_binding(LED0_LABEL);

    if ( dev_led0_green == NULL )
    { rstatus = ZR__WARNING__FAIL_ON_DEVICE_GET_BINDING; }

    if ( rstatus == ROUTINE_OK )
    {
        rstatus = gpio_pin_configure(dev_led0_green, LED0_PIN, GPIO_OUTPUT_ACTIVE | LED0_FLAGS);
        if ( rstatus < 0 )
        {
            rstatus = ZR__WARNING__FAIL_ON_GPIO_PIN_CONFIGURE;
        }
    }

    if ( rstatus == ROUTINE_OK )
    { gpio_pin_set(dev_led0_green, LED0_PIN, false); }

    return rstatus;
}




void main(void)
{
	uint32_t led_state = 0;
	uint32_t rstatus = 0;  // called routine status

	printk("Hello World! %s\n", CONFIG_BOARD);

        rstatus = app_config__configure_line__led0();

	while (1)
	{

#if 0
		if ( led_state == true )
			{ led_state = false; }
		else
			{ led_state = true; }

               	rstatus = gpio_pin_set(dev_led0_green, LED0_PIN, led_state);
#endif

               	rstatus = gpio_pin_set(dev_led0_green, LED0_PIN, true);
		k_sleep(K_MSEC(50));
               	rstatus = gpio_pin_set(dev_led0_green, LED0_PIN, false);


		k_sleep(K_MSEC(SLEEP_PERIOD_THREAD_MAIN_IN_MS));
	}
}
