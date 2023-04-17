#include "sensors.h"

static struct anjay_zephyr_ipso_sensor_context temperature_sensor_def[] = {
#if TEMPERATURE_AVAILABLE
	{ .name = "Temperature",
	  .unit = "Cel",
	  .device = DEVICE_DT_GET(TEMPERATURE_NODE),
	  .channel = SENSOR_CHAN_AMBIENT_TEMP,
	  .min_range_value = NAN,
	  .max_range_value = NAN }
#endif // TEMPERATURE_AVAILABLE
};

static struct anjay_zephyr_ipso_sensor_context humidity_sensor_def[] = {
#if HUMIDITY_AVAILABLE
	{ .name = "Humidity",
	  .unit = "%RH",
	  .device = DEVICE_DT_GET(HUMIDITY_NODE),
	  .channel = SENSOR_CHAN_HUMIDITY,
	  .min_range_value = NAN,
	  .max_range_value = NAN }
#endif // HUMIDITY_AVAILABLE
};

static struct anjay_zephyr_ipso_sensor_oid_set sensors_basic_oid_def[] = {
	{ .user_sensors = temperature_sensor_def,
	  .oid = 3303,
	  .user_sensors_array_length = AVS_ARRAY_SIZE(temperature_sensor_def) },
	{ .user_sensors = humidity_sensor_def,
	  .oid = 3304,
	  .user_sensors_array_length = AVS_ARRAY_SIZE(humidity_sensor_def) }
};

void sensors_install(anjay_t *anjay)
{
	anjay_zephyr_ipso_basic_sensors_install(anjay, sensors_basic_oid_def,
						AVS_ARRAY_SIZE(sensors_basic_oid_def));
}
