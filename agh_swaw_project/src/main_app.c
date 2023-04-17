/*
 * Copyright 2020-2023 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <anjay_zephyr/config.h>
#include <anjay_zephyr/lwm2m.h>
#include <anjay_zephyr/objects.h>

#include "sensors.h"

LOG_MODULE_REGISTER(main_app);

static avs_sched_handle_t update_objects_handle;

struct anjay_zephyr_network_preferred_bearer_list_t anjay_zephyr_config_get_preferred_bearers(void);

static int register_objects(anjay_t *anjay)
{
	sensors_install(anjay);
	return 0;
}

static void update_objects(avs_sched_t *sched, const void *anjay_ptr)
{
	anjay_t *anjay = *(anjay_t *const *)anjay_ptr;

	anjay_zephyr_ipso_sensors_update(anjay);

	AVS_SCHED_DELAYED(sched, &update_objects_handle,
			  avs_time_duration_from_scalar(1, AVS_TIME_S), update_objects, &anjay,
			  sizeof(anjay));
}

static int init_update_objects(anjay_t *anjay)
{
	avs_sched_t *sched = anjay_get_scheduler(anjay);

	update_objects(sched, &anjay);

	return 0;
}

static int clean_before_anjay_destroy(anjay_t *anjay)
{
	avs_sched_del(&update_objects_handle);

	return 0;
}

static int release_objects(void)
{
	return 0;
}

int lwm2m_callback(anjay_t *anjay, enum anjay_zephyr_lwm2m_callback_reasons reason)
{
	switch (reason) {
	case ANJAY_ZEPHYR_LWM2M_CALLBACK_REASON_INIT:
		return register_objects(anjay);
	case ANJAY_ZEPHYR_LWM2M_CALLBACK_REASON_ANJAY_READY:
		return init_update_objects(anjay);
	case ANJAY_ZEPHYR_LWM2M_CALLBACK_REASON_ANJAY_SHUTTING_DOWN:
		return clean_before_anjay_destroy(anjay);
	case ANJAY_ZEPHYR_LWM2M_CALLBACK_REASON_CLEANUP:
		return release_objects();
	default:
		return -1;
	}
}

void main(void)
{
	LOG_INF("Initializing Anjay-zephyr-client demo " CONFIG_ANJAY_ZEPHYR_VERSION);

	anjay_zephyr_lwm2m_set_user_callback(lwm2m_callback);

	anjay_zephyr_lwm2m_init_from_settings();
	anjay_zephyr_lwm2m_start();

	while (1) {
		k_sleep(K_SECONDS(1));
	}
}
