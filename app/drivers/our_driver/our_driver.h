#ifndef OUR_DRIVER_H_
#define OUR_DRIVER_H_
#include <errno.h>
#include <stdbool.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

struct our_driver_data {
    bool invert;
    int counts;
};

struct our_driver_api {
    struct sensor_driver_api sensor_api;
    int (*set_invert)(const struct device *dev, bool invert, int counts);
};

static inline int our_driver_set_invert(const struct device *dev, bool invert, int counts)
{
    const struct our_driver_api *api = (const struct our_driver_api *)dev->api;

    if (api->set_invert == NULL) {
        return -ENOSYS;
    }
    return api->set_invert(dev, invert, counts);
}

DEVICE_API_EXTENDS(our, sensor, sensor_api);


#endif /* OUR_DRIVER_H_ */