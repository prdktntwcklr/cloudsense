#include <zephyr/ztest.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#define SIM_NODE DT_ALIAS(simulated)

/* Helper to get the device */
static const struct device *get_simulated_sensor(void) {
    const struct device *dev = DEVICE_DT_GET(SIM_NODE);
    return dev;
}

/* Test: Ensure the device is ready after boot */
ZTEST(simulated_sensor_tests, test_sensor_ready) {
    const struct device *dev = get_simulated_sensor();
    zassert_true(device_is_ready(dev), "Sensor device is not ready");
}

/* Test: Verify the fetch and get logic */
ZTEST(simulated_sensor_tests, test_sensor_reading) {
    const struct device *dev = get_simulated_sensor();
    struct sensor_value val;

    // Test Fetch
    int ret = sensor_sample_fetch(dev);
    zassert_equal(ret, 0, "Sensor fetch failed with return code %d", ret);

    // Test Get
    ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    zassert_equal(ret, 0, "Sensor channel get failed");
    
    // Verify the simulated value
    int expected_temp = DT_PROP(SIM_NODE, base_temp);
    zassert_equal(val.val1, expected_temp, "Expected %d degrees, got %d", expected_temp, val.val1);
    zassert_equal(val.val2, 0, "Expected 0 micro-degrees, got %d", val.val2);
}

/* Define the test suite */
ZTEST_SUITE(simulated_sensor_tests, NULL, NULL, NULL, NULL, NULL);
