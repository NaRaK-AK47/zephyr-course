#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "our_driver.h"
static int cmd_channel_get_handler(const struct shell *shell, size_t argc, char **argv){

    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(shell, "Device %s not found", argv[1]);
        return -ENODEV;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_ALL, &val);
    if (ret) {  
        shell_error(shell, "Failed to get channel value: %d", ret);
        return ret;
    }

    shell_info(shell, "Channel value: %d", val.val1);

    return 0;
}

static int cmd_channel_fetch_handler(const struct shell *shell, size_t argc, char **argv){

    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(shell, "Device %s not found", argv[1]);
        return -ENODEV;
    }

    
    int ret = sensor_sample_fetch(dev);
    if (ret) {  
        shell_error(shell, "Failed to get channel value: %d", ret);
        return ret;
    }
    struct our_driver_data *data = dev->data;
    shell_info(shell, "Channel counts: %d", data->counts);

    return 0;
}


static int cmd_channel_info_handler(const struct shell *shell, size_t argc, char **argv){

    const struct device *dev = shell_device_get_binding(argv[1]);
    if (!dev) {
        shell_error(shell, "Device %s not found", argv[1]);
        return -ENODEV;
    }
   
    shell_info(shell, "device name : %s , device state : %d", dev->name, dev->state->initialized);

    return 0;
}
SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(fetch, NULL, "Fetch Channel of our driver", cmd_channel_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Read Channel of our driver", cmd_channel_get_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Info Channel of our driver", cmd_channel_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmd, "Our driver commands", NULL);