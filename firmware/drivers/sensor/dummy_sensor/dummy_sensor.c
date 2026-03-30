#define DT_DRV_COMPAT cloudsense_dummy_sensor

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

struct dummy_sensor_data {
    int16_t temp;
};

static int dummy_sample_fetch(const struct device *dev, enum sensor_channel chan) {
    struct dummy_sensor_data *data = dev->data;
    data->temp = 25; // Simulate a constant 25°C
    return 0;
}

static int dummy_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    struct dummy_sensor_data *data = dev->data;
    val->val1 = data->temp;
    val->val2 = 0;
    return 0;
}

static int dummy_init(const struct device *dev) {
    return 0;
}

static const struct sensor_driver_api dummy_sensor_api = {
    .sample_fetch = dummy_sample_fetch,
    .channel_get = dummy_channel_get,
};

#define DUMMY_SENSOR_CREATE_INST(inst) \
    static struct dummy_sensor_data dummy_sensor_drv_##inst; \
    DEVICE_DT_INST_DEFINE(inst, \
                          dummy_init, \
                          NULL, \
                          &dummy_sensor_drv_##inst, \
                          NULL, \
                          POST_KERNEL, \
                          CONFIG_SENSOR_INIT_PRIORITY, \
                          &dummy_sensor_api);

DT_INST_FOREACH_STATUS_OKAY(DUMMY_SENSOR_CREATE_INST)
