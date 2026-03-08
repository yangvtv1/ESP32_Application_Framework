/*
 *              Copyright (c)  2026
 *  File header: 		mqtt.c
 *  Created on : 		March 03, 2026
 *      Author : 		R&D Firmware Team (Firmware Developer)
 *      Contact:        elvis.luong@gmail.com
 */


#include "ext_mqtt.h"


/******************************************************************************/
/******************************************************************************/
/***                           Private definitions                           **/
/******************************************************************************/
/******************************************************************************/
ext_mqtt_t MQTT;
/******************************************************************************/
/******************************************************************************/
/***                      Private functions declare                          **/
/******************************************************************************/
/******************************************************************************/
static const char *TAG = "mqtt_example";
/******************************************************************************/
/******************************************************************************/
/***                                Global Parameters                        **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                            Private functions                            **/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/***                      Processing functions Callback                      **/
/******************************************************************************/
/******************************************************************************/

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        // msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
        msg_id = esp_mqtt_client_publish(client, "v1/devices/me/telemetry", "{\"temp\":25}", 0, 1, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "v1/devices/me/attributes", 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
        ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
        break;
    // case MQTT_EVENT_CONNECTED:
    // {
    //     uint32_t counter = 0;
    //     char buf[50] = "";
    //     ESP_LOGI(TAG, "Connected → start sending telemetry");

    //     while (1) {
    //         sprintf(buf, "{\"temp\":%ld}", counter++);
    //         esp_mqtt_client_publish(client,
    //                                 "v1/devices/me/telemetry",
    //                                 buf,
    //                                 0, 1, 0);
    //         vTaskDelay(5000 / portTICK_PERIOD_MS);
    //     }
    // }
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        // msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
        msg_id = esp_mqtt_client_publish(client, "v1/devices/me/telemetry", "{\"temp\":25}", 0, 1, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            // log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            // log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            // log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

void mqtt_app_start(void){
    esp_mqtt_client_config_t mqtt_cfg = {
        // .broker.address.uri = "mqtt://mqtt.namismart.vn:1883",
        // .credentials.username = "namismart",
        // .credentials.authentication.password = "Q7bjvdqxCzXb7Cy",


        .broker.address.uri = "mqtt://app.coreiot.io:1883",

        .credentials = {
            .username = "dol8xpgplnxv32agyfam",
        },

    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    // /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}
/******************************************************************************/
/******************************************************************************/
/***                            MainRun functions                            **/
/******************************************************************************/
/*******************************************************b***********************/

/******************************************************************************/
/******************************************************************************/
/***                            Public functions                             **/
/******************************************************************************/
/******************************************************************************/
void initial(void){
    memset(&MQTT, 0x00, sizeof(MQTT));
    MQTT.Initial                 = &initial;
    MQTT.mqttAppStart            = &mqtt_app_start;
    MQTT.mqttEventHandler        = &mqtt_event_handler;

    // MQTT.mqttAppStart();
}
/******************************************************************************/
/******************************************************************************/
/***                            Library callback                             **/
/******************************************************************************/
/******************************************************************************/




