#ifndef SENSOR_H
#define SENSOR_H

#include "driver/gpio.h"

#define TRIG_PIN GPIO_NUM_19
#define ECHO_PIN GPIO_NUM_34

void sensor_init(void);
float sensor_get_distance(void);

#endif