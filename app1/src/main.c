/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log_ctrl.h>

#include "usr_fun.h"
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

#define STACKSIZE	500

#define CONFIG_LOG_TIMESTAMPING 0
/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);



void blink0(void)
{
	gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	while(1){
		gpio_pin_toggle_dt(&led0);
		k_msleep(200);
	}

}

void blink1(void)
{
	gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);

	while (1){
		gpio_pin_toggle_dt(&led1);
		k_msleep(400);
	}
		

}

int main(void)
{	
	gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);

	gpio_pin_set_dt(&led2, true);
	
	#ifdef CONFIG_USR_FUN
    	usr_fun();
	#endif
	
	return 0;
}

K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(blink1_id, STACKSIZE, blink1, NULL, NULL, NULL, 7, 0, 0);

