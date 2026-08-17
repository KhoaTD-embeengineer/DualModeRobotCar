#include "bluetooth_app.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"
#include "nvs_flash.h"
#include "nvs.h"

#define TAG "BT_APP"
#define DEVICE_NAME "Robot_DualMode" // ten hien thi khi bat dien thoai len do

QueueHandle_t bt_queue = NULL;

//Callback
static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
        case ESP_SPP_INIT_EVT:
            ESP_LOGI(TAG, "Bluetooth da khoi tao xong!");
            //chay dich sever
            esp_spp_start_srv(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_SLAVE, 0, "SPP_SERVER");
            break;

        case ESP_SPP_START_EVT:
            ESP_LOGI(TAG, "Dich vu SPP da bat dau chay!");
            //cho phep cac thiet bi khac tim thay
            esp_bt_gap_set_device_name(DEVICE_NAME);
            esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
            break;

        case ESP_SPP_DATA_IND_EVT: // nhan du lieu
            ESP_LOGI(TAG, "Da nhan du lieu tu App, do dai: %d", param->data_ind.len);
            
            //lay ki tu dau tien trong mang
            char command = param->data_ind.data[0];
            
            //day vao hang doi 
            // day thi bo qua, khong cho
            if (bt_queue != NULL) {
                xQueueSend(bt_queue, &command, 0);
            }
            break;

        case ESP_SPP_SRV_OPEN_EVT:
            ESP_LOGI(TAG, "Dien thoai da ket noi thanh cong voi Robot!");
            break;

        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(TAG, "Dien thoai da ngat ket noi!");
            break;

        default:
            break;
    }
}

void bluetooth_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));
    
    bt_queue = xQueueCreate(10, sizeof(char));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BTDM)); 

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_ERROR_CHECK(esp_spp_register_callback(esp_spp_cb));
    
    esp_spp_cfg_t spp_cfg = {
        .mode = ESP_SPP_MODE_CB,
        .enable_l2cap_ertm = true,
        .tx_buffer_size = 0, 
    };
    ESP_ERROR_CHECK(esp_spp_enhanced_init(&spp_cfg));
}

char bluetooth_read_char(void) {
    char cmd = '\0';
    if (bt_queue != NULL) 
    {
        if (xQueueReceive(bt_queue, &cmd, 0) == pdTRUE) 
        {
            return cmd;
        }
    }
    return '\0';
}