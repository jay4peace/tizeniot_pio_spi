#ifndef _SOUND_SENSOR_H_
#define _SOUND_SENSOR_H_

int sound_sensor_read(int ch_num, unsigned int *out_value);
void sound_sensor_close(void);

#endif /* _SOUND_SENSOR_H_ */
