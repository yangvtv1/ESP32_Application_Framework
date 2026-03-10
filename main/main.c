#include "main.h"

application_t Application;
static const char *TAG = "mqtt_example";

void InitialGeneral(void){
    memset(&Application, 0x00, sizeof(Application));
    Application.mqtt.mqttAppStart     = &mqtt_app_start;
    Application.wifi.wifi_init        = &ext_wifi_init;
    Application.wifi.wifi_connect     = &ext_wifi_connect;
    nvs_flash_init();
}

void app_main(void)
{
    InitialGeneral();
    ESP_LOGI(TAG, "[APP] LTH Group hello");
    Application.wifi.wifi_init();

    // Application.wifi.wifi_connect("Cao Cuong 2.","0967859714");
    Application.wifi.wifi_connect("IoT Test 2","iotnami@2468");
}
