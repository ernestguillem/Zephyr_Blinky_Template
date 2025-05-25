/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/random/random.h>
#include "usr_fun.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

int main(void)
{
	bool led_state = true;
	uint32_t rnd = 0;

	if (!gpio_is_ready_dt(&led0) && !gpio_is_ready_dt(&led1) && !gpio_is_ready_dt(&led2) ) {
		return 0;
	}

	if(gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE) < 0){
		return 0;
	};
	if(gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE) < 0){
		return 0;
	};
	if(gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE) < 0){
		return 0;
	};
	gpio_pin_set_dt(&led2, true);
	
	#ifdef CONFIG_USR_FUN
    usr_fun();
	#endif

	while (1) {
		rnd = sys_rand32_get();
		gpio_pin_toggle_dt(&led0);
		gpio_pin_toggle_dt(&led1);
	
		led_state = !led_state;
		printk("LED state: %s - Random: %u\n", led_state ? "ON" : "OFF", rnd);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
