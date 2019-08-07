/* ****************************************************************
 *
 * Copyright 2017 Samsung Electronics All Rights Reserved.
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

#include "as-log.h"
#include "adc-mcp3008.h"

static int initialized = 0;

extern void print_bar(unsigned int val);

void sound_sensor_close(void)
{
	adc_mcp3008_fini();
	initialized = 0;
}

int sound_sensor_read(int ch_num, unsigned int *out_value)
{
	unsigned int read_value = 0;
	int ret = 0;

	if (!initialized) {
		ret = adc_mcp3008_init();
		retv_if(ret != 0, -1);
		initialized = 1;
	}

	ret = adc_mcp3008_read(ch_num, &read_value);
	retv_if(ret != 0, -1);

	print_bar(read_value);

	*out_value = read_value;

	return 0;
}
