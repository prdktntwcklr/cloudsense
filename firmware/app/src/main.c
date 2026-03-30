#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>

int main(void) {
    const struct device *dev = DEVICE_DT_GET(DT_ALIAS(temp_sensor));

    printk("Hello World!\n");

    if (!device_is_ready(dev)) {
        printk("Device %s is not ready\n", dev->name);
        return -1;
    }

    printk("Hello from CloudSense!\n");

    struct sensor_value temp;

    while (1) {
        sensor_sample_fetch(dev);
        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        printk("Temperature: %d.%06d C\n", temp.val1, temp.val2);

        printk("Heartbeat: %lld ms\n", k_uptime_get());
        k_msleep(1000);
    }

    return 0;
}
