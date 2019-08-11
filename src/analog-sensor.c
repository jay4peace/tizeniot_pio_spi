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
#include <Ecore.h>
#include "as-log.h"
#include "sound-sensor.h"

typedef struct _app_data {
	Ecore_Idler *idler;
}app_data;

static Eina_Bool __get_value(void *data)
{
	int ret = 0;
	unsigned int value = 0;

	app_data *ad = data;

	if (!ad) {
		_E("failed to get app_data");
		service_app_exit();
		return ECORE_CALLBACK_CANCEL;
	}

	ret = sound_sensor_read(0, &value);
	retv_if(ret != 0, ECORE_CALLBACK_RENEW);

//	_D("sensor value - [%u]", value);

	return ECORE_CALLBACK_RENEW;
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

	if (ad->idler) {
		ecore_idler_del(ad->idler);
		ad->idler = NULL;
	}

	ad->idler = ecore_idler_add(__get_value, ad);
	if (!ad->idler)
		_E("Failed to add idler");

    return;
}

int main(int argc, char* argv[])
{
	app_data ad;
	service_app_lifecycle_callback_s event_callback;

	ad.idler = NULL;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, &ad);
}
