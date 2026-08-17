#ifndef BLUETOOTH_APP_H
#define BLUETOOTH_APP_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

// Khai báo một Hàng đợi (Queue) toàn cục để chia sẻ dữ liệu giữa Bluetooth và file Main
extern QueueHandle_t bt_queue;

// Hàm khởi tạo toàn bộ cấu hình Bluetooth
void bluetooth_init(void);
char bluetooth_read_char(void);

#endif