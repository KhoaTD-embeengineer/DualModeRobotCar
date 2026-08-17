#include "sensor.h"
#include "rom/ets_sys.h"
#include "esp_timer.h"

void sensor_init(void)
{
    gpio_reset_pin(TRIG_PIN);
    gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(TRIG_PIN, 0);

    gpio_reset_pin(ECHO_PIN);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
}

//ham do khoang cach
float sensor_get_distance(void)
{
    gpio_set_level(TRIG_PIN, 0);
    ets_delay_us(2);
    gpio_set_level(TRIG_PIN, 1);
    ets_delay_us(10);
    gpio_set_level(TRIG_PIN, 0);

    int64_t start_time = esp_timer_get_time();
    // tranh loi treo chip neu khong co cam bien
    while(gpio_get_level(ECHO_PIN) == 0)
    {
        if (esp_timer_get_time() - start_time > 30000) return -1.0;
        
    }

    int64_t echo_start = esp_timer_get_time();
    while(gpio_get_level(ECHO_PIN) == 1)
    {
        if(esp_timer_get_time() - echo_start > 30000) 
            return -1.0;
    }

    int64_t echo_end = esp_timer_get_time();
    int64_t time_duration = echo_end - echo_start;
    float distance = (time_duration * 0.0343) / 2.0;

    if(distance > 400.0) return 1.0;
    return distance;
}