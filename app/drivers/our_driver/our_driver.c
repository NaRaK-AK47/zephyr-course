#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include "our_driver.h"
#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_config {
    struct gpio_dt_spec led;
};



static int set_invert_impl(const struct device *dev, bool invert,int counts)
{
    struct our_driver_data *data = dev->data;

    data->invert = invert;
    data->counts = counts;
    LOG_INF("invert set to %d counts = %d for device %s", invert, data->counts, dev->name);
    return 0;
}

static int channel_get_my_impl(const struct device *dev,
     enum sensor_channel chan, 
     struct sensor_value *val)

{
    const struct our_driver_config *cfg = dev->config;
    struct our_driver_data *data = dev->data;
    LOG_INF("Called get from our driver %s, channel %d data->invert = %d data->counts = %d", dev->name, chan, data->invert, data->counts);
    return gpio_pin_set_dt(&cfg->led, data->invert ? 0 : 1);  
    
}

 int channel_fetch_my_impl(const struct device *dev,
				     enum sensor_channel chan)
{

    const struct our_driver_config *cfg = dev->config;
    struct our_driver_data *data = dev->data;
    LOG_INF("Called fetch from our driver %s, channel %d data->invert = %d data->counts = %d", dev->name, chan, data->invert, data->counts);
    return gpio_pin_set_dt(&cfg->led, data->invert ? 0 : 1);  
   
}

static DEVICE_API(our, api_iomico_lecture) = {
    .sensor_api = {
        .sample_fetch = channel_fetch_my_impl,
        .channel_get  = channel_get_my_impl,
    },
    .set_invert = set_invert_impl,
};  

static int init(const struct device *dev)
{
    LOG_INF("Hello From Init, device %s", dev->name);
    const struct our_driver_config *cfg = dev->config;
    if (!gpio_is_ready_dt(&cfg->led)) return -ENODEV;

    return gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_ACTIVE);
     
}

#define DEV_INST(inst)                                                  \
    static struct our_driver_data data_##inst;                          \
    static const struct our_driver_config config_##inst = {             \
        .led = GPIO_DT_SPEC_INST_GET(inst, led_gpios),                  \
    };                                                                  \
    DEVICE_DT_INST_DEFINE(inst, init, NULL,  &data_##inst, &config_##inst,       \
                          POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,     \
                          &api_iomico_lecture)

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);