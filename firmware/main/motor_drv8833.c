#include "motor_drv8833.h"

//ham khoi tao motor
void motor_init(void)
{
    gpio_reset_pin(MOTOR_LEFT_IN1);
    gpio_reset_pin(MOTOR_LEFT_IN2);
    gpio_reset_pin(MOTOR_RIGHT_IN1);
    gpio_reset_pin(MOTOR_RIGHT_IN2);

    gpio_set_direction(MOTOR_LEFT_IN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_LEFT_IN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_RIGHT_IN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_RIGHT_IN2, GPIO_MODE_OUTPUT);
}

//ham tien
void motor_move_forward()
{
    gpio_set_level(MOTOR_LEFT_IN1, 1);
    gpio_set_level(MOTOR_LEFT_IN2, 0);
    gpio_set_level(MOTOR_RIGHT_IN1, 1);
    gpio_set_level(MOTOR_RIGHT_IN2, 0);
}

//ham dung
void motor_stop()
{
    gpio_set_level(MOTOR_LEFT_IN1, 0);
    gpio_set_level(MOTOR_LEFT_IN2, 0);
    gpio_set_level(MOTOR_RIGHT_IN1, 0);
    gpio_set_level(MOTOR_RIGHT_IN2, 0);
}

//ham lui
void motor_move_backward()
{
    gpio_set_level(MOTOR_LEFT_IN1, 0);
    gpio_set_level(MOTOR_LEFT_IN2, 1);
    gpio_set_level(MOTOR_RIGHT_IN1, 0);
    gpio_set_level(MOTOR_RIGHT_IN2, 1);
}

//ham xoay trai
void motor_turn_left()
{
    gpio_set_level(MOTOR_LEFT_IN1, 0);
    gpio_set_level(MOTOR_LEFT_IN2, 1);
    gpio_set_level(MOTOR_RIGHT_IN1, 1);
    gpio_set_level(MOTOR_RIGHT_IN2, 0);
}

//ham xoay phai
void motor_turn_right()
{
    gpio_set_level(MOTOR_LEFT_IN1, 1);
    gpio_set_level(MOTOR_LEFT_IN2, 0);
    gpio_set_level(MOTOR_RIGHT_IN1, 0);
    gpio_set_level(MOTOR_RIGHT_IN2, 1);
}