#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
    struct gpio_dt_spec led;
};

static int channel_get_my_impl(const struct device *dev,
     enum sensor_channel chan, 
     struct sensor_value *val)

{
    const struct our_driver_config *cfg = dev->config;
                 // ON
    LOG_INF("Led turned off for device %s, channel %d", dev->name, chan);
    return gpio_pin_set_dt(&cfg->led, 0);  
    
}

 int channel_fetch_my_impl(const struct device *dev,
				     enum sensor_channel chan)
{

    const struct our_driver_config *cfg = dev->config;
    LOG_INF("Led turned on for device %s, channel %d", dev->name, chan);
    return gpio_pin_set_dt(&cfg->led, 1);  
   
}

static DEVICE_API(sensor,api_iomico_lecture) = {
    .channel_get = channel_get_my_impl,
    .sample_fetch = channel_fetch_my_impl,
};   

static int init(const struct device *dev)
{
    LOG_INF("Hello From Init, device %s", dev->name);
    const struct our_driver_config *cfg = dev->config;
    if (!gpio_is_ready_dt(&cfg->led)) return -ENODEV;

    return gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_ACTIVE);
     
}

#define DEV_INST(inst)                                                  \
    static const struct our_driver_config config_##inst = {             \
        .led = GPIO_DT_SPEC_INST_GET(inst, led_gpios),                  \
    };                                                                  \
    DEVICE_DT_INST_DEFINE(inst, init, NULL, NULL, &config_##inst,       \
                          POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,     \
                          &api_iomico_lecture)

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);