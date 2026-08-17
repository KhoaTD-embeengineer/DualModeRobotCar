#ifndef SERVO_CTRL_H
#define SERVO_CTRL_H

#include "driver/gpio.h"

#define SERVO_PIN GPIO_NUM_18

#define SERVO_MIN_PWM 500
#define SERVO_MAX_PWM 2500
#define SERVO_MAX_DEGREE 180

void servo_init(void);
void servo_set_rotate(int angle);

#endif