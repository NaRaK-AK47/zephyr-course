#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
//#define LED_NODE DT_NODELABEL(warning_led)

//#define LED_NODE DT_ALIAS(app_led)

//#define LED_NODE DT_PATH(leds, led1)

//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace{
    void test(){
        const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        int ret1 = sensor_sample_fetch(dev);
        k_msleep(SLEEP_TIME_MS);
        int ret2 = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
        LOG_INF("sensor_channel_get returned = %d", ret2);
    }
}

int main(void)
{
   // test();

    const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        
       // LOG_INF("sensor_channel_get returned = %d", ret2);
    // bool led_state = true;

    // if (!gpio_is_ready_dt(&led)) return 0;

    // if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

     while (1) {

    int ret1 = sensor_sample_fetch(dev);
        k_msleep(SLEEP_TIME_MS);
        int ret2 = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
        k_msleep(SLEEP_TIME_MS);
    //     if (gpio_pin_toggle_dt(&led) < 0) return 0;

    //     led_state = !led_state;
    //     LOG_INF("LED statesssss: %s", led_state ? "ON" : "OFF");
    //     k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
