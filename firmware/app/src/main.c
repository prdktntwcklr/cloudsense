#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/sensor.h>

/**
 * @brief Get the temperature from the sensor
 *
 * @param dev Pointer to the device structure for the temperature sensor
 * @param temp Pointer to a sensor_value structure to store the temperature reading
 *
 * @return 0 on success, negative error code on failure
 *
 */
int get_temperature(const struct device *dev, struct sensor_value *temp) {
    __ASSERT(dev != NULL, "Sensor device pointer is NULL");
    __ASSERT(temp != NULL, "Temperature value pointer is NULL");

    int rc = sensor_sample_fetch(dev);
    if (rc != 0) {
        printk("Failed to fetch sensor sample: %d\n", rc);
        return rc;
    }

    return sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, temp);
}

/**
 * @brief Main function for the CloudSense application
 */
int main(void) {
    const struct device *temp_sensor = DEVICE_DT_GET(DT_ALIAS(temp_sensor));

    if (!device_is_ready(temp_sensor)) {
        printk("Sensor %s not ready", temp_sensor->name);
        return -ENODEV;
    }

    printk("Hello from CloudSense!\n");

    while (1) {
        struct sensor_value temp;

        int rc = get_temperature(temp_sensor, &temp);
        if (rc == 0) {
            printk("Temperature: %d.%06d C\n", temp.val1, temp.val2);
        }
        else {
            printk("Error reading temperature: %d\n", rc);
        }

        int64_t uptime_ms = k_uptime_get();
        printk("System uptime: %lld ms\n", uptime_ms);

        k_msleep(1000);
    }

    /* this line is never reached */
    return 0;
}
