#define DT_DRV_COMPAT cloudsense_simulated_sensor

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(SIMULATED_SENSOR, CONFIG_SENSOR_LOG_LEVEL);

struct simulated_sensor_data {
    int16_t temp;
};

struct simulated_sensor_config {
    int16_t base_temp;
};

static int simulated_sensor_sample_fetch(const struct device *dev, enum sensor_channel chan) {
    if (chan != SENSOR_CHAN_ALL && chan != SENSOR_CHAN_AMBIENT_TEMP) {
        return -ENOTSUP;
    }

    struct simulated_sensor_data *data = dev->data;
    const struct simulated_sensor_config *cfg = dev->config;

    data->temp = cfg->base_temp;

    return 0;
}

static int simulated_sensor_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val) {
    if (chan != SENSOR_CHAN_AMBIENT_TEMP) {
        return -ENOTSUP;
    }
    
    struct simulated_sensor_data *data = dev->data;
    val->val1 = data->temp;
    val->val2 = 0;

    return 0;
}

static int simulated_sensor_init(const struct device *dev) {
    return 0;
}

static const struct sensor_driver_api simulated_sensor_api = {
    .sample_fetch = simulated_sensor_sample_fetch,
    .channel_get = simulated_sensor_channel_get,
};

#define SIMULATED_SENSOR_CREATE_INST(inst)                                     \
    static struct simulated_sensor_data simulated_sensor_drv_##inst;           \
                                                                               \
    static const struct simulated_sensor_config                                \
        simulated_sensor_cfg_##inst = {                                        \
            .base_temp = DT_INST_PROP(inst, base_temp),                        \
    };                                                                         \
                                                                               \
    DEVICE_DT_INST_DEFINE(inst,                                                \
                          simulated_sensor_init,                               \
                          NULL,                                                \
                          &simulated_sensor_drv_##inst,                        \
                          &simulated_sensor_cfg_##inst,                        \
                          POST_KERNEL,                                         \
                          CONFIG_SENSOR_INIT_PRIORITY,                         \
                          &simulated_sensor_api);

DT_INST_FOREACH_STATUS_OKAY(SIMULATED_SENSOR_CREATE_INST)
