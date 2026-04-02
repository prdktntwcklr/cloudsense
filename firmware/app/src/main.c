#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(cloudsense, LOG_LEVEL_INF);

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
        LOG_ERR("Failed to fetch sensor sample: %d", rc);
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
        LOG_ERR("Sensor %s not ready", temp_sensor->name);
        return -ENODEV;
    }

    LOG_INF("Hello from CloudSense!");

    while (1) {
        struct sensor_value temp;

        int rc = get_temperature(temp_sensor, &temp);
        if (rc == 0) {
            LOG_INF("Temperature: %d.%06d C", temp.val1, temp.val2);
        }
        else {
            LOG_WRN("Error reading temperature: %d", rc);
        }

        k_msleep(1000);
    }

    /* this line is never reached */
    return 0;
}
