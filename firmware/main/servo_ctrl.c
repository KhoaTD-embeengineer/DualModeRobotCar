#include "servo_ctrl.h"
#include "driver/ledc.h" // thu vien tao xung PWM cua esp32

void servo_init(void)
{
    //cau hinh bo dem cho PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT, //(0-8191)
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    //cau hinh xuat tin hieu
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = SERVO_PIN,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

void servo_set_rotate(int angle)
{
    if(angle < 0) angle = 0;
    if(angle > SERVO_MAX_DEGREE) angle = SERVO_MAX_DEGREE;

    uint32_t pw = SERVO_MIN_PWM + ((SERVO_MAX_PWM - SERVO_MIN_PWM) * angle)/SERVO_MAX_DEGREE;
    uint32_t duty = (pw*8192)/20000;

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}