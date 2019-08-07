/* ****************************************************************
 *
 * Copyright 2019 Jeonghoon Park All rights reserved.
 *
 * Contact: Jeonghoon Park <jeonghoon79@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include <tizen.h>
#include <service_app.h>
#include <glib.h>
#include "as-log.h"
#include "sound-sensor.h"

#define GETTER_INTERVAL (5) //5ms

typedef struct _app_data {
	guint getter_id;
}app_data;

static gboolean __get_value(gpointer user_data)
{
	int ret = 0;
	unsigned int value = 0;

	app_data *ad = user_data;

	if (!ad) {
		_E("failed to get app_data");
		service_app_exit();
		return FALSE;
	}

	ret = sound_sensor_read(0, &value);
	retv_if(ret != 0, TRUE);

//	_D("sensor value - [%u]", value);

	return TRUE;
}


static bool service_app_create(void *data)
{
    return true;
}

static void service_app_terminate(void *data)
{
	sound_sensor_close();
    return;
}

static void service_app_control(app_control_h app_control, void *data)
{
	app_data *ad = data;
	ret_if(!ad);

	if (ad->getter_id) {
		g_source_remove(ad->getter_id);
		ad->getter_id = 0;
	}

	ad->getter_id = g_timeout_add(GETTER_INTERVAL, __get_value, ad);
	if (!ad->getter_id)
		_E("Failed to add getter");

    return;
}

int main(int argc, char* argv[])
{
	app_data ad;
	service_app_lifecycle_callback_s event_callback;

	ad.getter_id = 0;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, &ad);
}
