#ifndef MOTOR_DRV8833_H
#define MOTOR_DRV8833_H

#include "driver/gpio.h"

#define MOTOR_LEFT_IN1 GPIO_NUM_32
#define MOTOR_LEFT_IN2 GPIO_NUM_27
#define MOTOR_RIGHT_IN1 GPIO_NUM_26
#define MOTOR_RIGHT_IN2 GPIO_NUM_25

void motor_init(void);
void motor_move_forward();
void motor_stop();
void motor_turn_left();
void motor_turn_right();
void motor_move_backward();
#endif