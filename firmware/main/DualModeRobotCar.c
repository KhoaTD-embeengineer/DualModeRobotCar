#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor_drv8833.h"
#include "sensor.h"
#include "servo_ctrl.h"
#include "bluetooth_app.h"

typedef enum
{
    MODE_MANUAL,
    MODE_AUTO
} RobotMode;

volatile RobotMode current_mode = MODE_MANUAL;

//Xu li Bluetooth va dieu khien tay
void bluetooth_control_mode(void *pvPara)
{
    char cmd;
    while(1)
    {
        cmd = bluetooth_read_char();
        if(cmd != '\0')
        {
            if(cmd == 'A')
            {
                current_mode = MODE_AUTO;
            }
            else if(cmd == 'M')
            {
                current_mode = MODE_MANUAL;
                motor_stop();
            }
            else if(current_mode == MODE_MANUAL)
            {
                switch (cmd)
                {
                case 'F': motor_move_forward(); break;
                case 'B': motor_move_backward(); break;
                case 'R': motor_turn_right(); break;
                case 'L': motor_turn_left(); break;
                case 'S': motor_stop(); break;    
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50)); //chong treo CPU khi o che do auto
    }
}

//Thuat toan tu dong lai
void auto_drive_task(void *pvPara)
{
    float dis_front, dis_left, dis_right;

    while(1)
    {
        if(current_mode == MODE_AUTO)
        {
            dis_front = sensor_get_distance();
            if(dis_front > 25.0 || dis_front < 0)
            {
                motor_move_forward();
            }
            else
            {
                motor_stop();
                vTaskDelay(pdMS_TO_TICKS(200));
                servo_set_rotate(180);
                vTaskDelay(pdMS_TO_TICKS(500));
                dis_left = sensor_get_distance();
                servo_set_rotate(0);
                vTaskDelay(pdMS_TO_TICKS(500));
                dis_right = sensor_get_distance();
                servo_set_rotate(90);
                vTaskDelay(pdMS_TO_TICKS(500));

                if(dis_left > 25.0)
                {
                    motor_turn_left();
                    vTaskDelay(pdMS_TO_TICKS(250));
                    motor_stop();
                }
                else if(dis_right > 25.0)
                {
                    motor_turn_right();
                    vTaskDelay(pdMS_TO_TICKS(250));
                    motor_stop();
                }
                else
                {
                    motor_move_backward();
                    vTaskDelay(pdMS_TO_TICKS(600));
                    motor_turn_left();
                    vTaskDelay(pdMS_TO_TICKS(500));
                    motor_stop();
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // chong treo CPU khi manual
    }
}

void app_main(void)
{
    motor_init();
    bluetooth_init();
    servo_init();
    sensor_init();

    servo_set_rotate(90);

    xTaskCreate(bluetooth_control_mode, "Manual_Mode", 2048, NULL, 5, NULL);
    xTaskCreate(auto_drive_task, "Auto_Mode", 2048, NULL, 5, NULL);
}
