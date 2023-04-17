#pragma once

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#include <anjay_zephyr/ipso_objects.h>

#define TEMPERATURE_NODE DT_ALIAS(temperature)
#define TEMPERATURE_AVAILABLE DT_NODE_HAS_STATUS(TEMPERATURE_NODE, okay)

#define HUMIDITY_NODE DT_ALIAS(humidity)
#define HUMIDITY_AVAILABLE DT_NODE_HAS_STATUS(HUMIDITY_NODE, okay)

void sensors_install(anjay_t *anjay);
