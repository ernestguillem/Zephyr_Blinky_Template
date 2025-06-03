
// Content of usr_fun.c
#include "usr_fun.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/dac.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>


LOG_MODULE_REGISTER(usr_fun, CONFIG_LOG_DEFAULT_LEVEL);

#ifdef CONFIG_USR_FUN

// Get a handle to the DAC device defined in the Devicetree with label "dac0"
const struct device *dac_dev = DEVICE_DT_GET(DT_NODELABEL(dac0));

const struct device *vref_dev = DEVICE_DT_GET(DT_NODELABEL(vref));

struct sensor_value vdd;

// Define the DAC channel configuration
struct dac_channel_cfg ch_cfg = {
    .channel_id = 0,     // MCP4725 has only one channel (channel 0)
    .resolution = 12,    // MCP4725 is a 12-bit DAC
};

void usr_fun(void) {
    printk("Message in a user function\n");
}

void dac_init(void)
{
  // Check if the DAC device is ready for use
  if (!device_is_ready(dac_dev)) {
    printk("DAC device not ready!\n");
    return;
  }

  // Set up the DAC channel with the specified configuration
  if (dac_channel_setup(dac_dev, &ch_cfg) != 0) {
    printk("DAC channel setup failed\n");
    return;
  }

  if (dac_write_value(dac_dev, 0, 0) != 0) {
    printk("DAC write failed\n");
  } else {
    printk("DAC output set to mid-scale\n");
  }
}

void dac_set(uint16_t newValue){
  // Set up the DAC channel with the specified configuration
  if (dac_write_value(dac_dev, 0, newValue) == 0) {
    LOG_INF("Dac's new value: %d", newValue);
  }
}

// Get device from DT label
void vref_log(void) {
  if (!device_is_ready(vref_dev)) {
    LOG_ERR("VREF device not ready");
    return;
  }

  int ret = sensor_sample_fetch(vref_dev);
  if (ret < 0) {
    LOG_ERR("Failed to fetch VREF sample (%d)", ret);
    return;
  }

  ret = sensor_channel_get(vref_dev, SENSOR_CHAN_VOLTAGE, &vdd);
  if (ret < 0) {
    LOG_ERR("Failed to read VDD (%d)", ret);
    return;
  }

  LOG_INF("VDD = %d.%03d V", vdd.val1, vdd.val2);
}

#else
void usr_fun(void){}

void dac_set(uint16_t newValue){}

void dac_init(void){
  LOG_WRN("DAC not enabled");
}

void vref_log(void){}

#endif
