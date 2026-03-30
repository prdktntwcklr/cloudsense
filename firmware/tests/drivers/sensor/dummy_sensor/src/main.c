#include <zephyr/ztest.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

/* Helper to get the device */
static const struct device *get_dummy_sensor(void) {
    const struct device *dev = DEVICE_DT_GET(DT_ALIAS(dummy));
    return dev;
}

/* Test: Ensure the device is ready after boot */
ZTEST(dummy_sensor_tests, test_sensor_ready) {
    const struct device *dev = get_dummy_sensor();
    zassert_true(device_is_ready(dev), "Sensor device is not ready");
}

/* Test: Verify the fetch and get logic */
ZTEST(dummy_sensor_tests, test_sensor_reading) {
    const struct device *dev = get_dummy_sensor();
    struct sensor_value val;

    // Test Fetch
    int ret = sensor_sample_fetch(dev);
    zassert_equal(ret, 0, "Sensor fetch failed with return code %d", ret);

    // Test Get
    ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    zassert_equal(ret, 0, "Sensor channel get failed");
    
    // Verify the simulated value (25.0)
    zassert_equal(val.val1, 25, "Expected 25 degrees, got %d", val.val1);
    zassert_equal(val.val2, 0, "Expected 0 micro-degrees, got %d", val.val2);
}

/* Define the test suite */
ZTEST_SUITE(dummy_sensor_tests, NULL, NULL, NULL, NULL, NULL);
