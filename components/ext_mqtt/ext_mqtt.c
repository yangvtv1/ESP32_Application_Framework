/*
 * ext_mqtt.c
 * Tuya MQTT implementation
 */

#include "ext_mqtt.h"
#include "mbedtls/md.h"
#include <sys/time.h>

extern const uint8_t tuya_root_pem_start[] asm("_binary_tuya_root_pem_start");
extern const uint8_t tuya_root_pem_end[]   asm("_binary_tuya_root_pem_end");

#define TUYA_DEVICE_ID     "2686d69e36dcdf359btdn8"
#define TUYA_DEVICE_SECRET "TTOCz7jhGJhqRffV"
#define TUYA_BROKER        "mqtts://m1.tuyacn.com:8883"

static const char *TAG = "ext_mqtt";

ext_mqtt_t MQTT;

static esp_mqtt_client_handle_t client;

static char username[200];
static char password[80];
static char clientid[80];

static char topic_pub[128];
static char topic_sub[128];




/********************************************************
                    username
********************************************************/

static void build_username(long long ts)
{
    sprintf(username,
            "%s|signMethod=hmacSha256,timestamp=%lld,secureMode=1,accessType=1",
            TUYA_DEVICE_ID,
            ts);
}



/********************************************************
                    password
********************************************************/

static void build_password(long long ts)
{
    char content[128];
    unsigned char hmac[32];

    sprintf(content,
        "deviceId=%s,timestamp=%lld,secureMode=1,accessType=1",
        TUYA_DEVICE_ID,
        ts);

    mbedtls_md_context_t ctx;
    const mbedtls_md_info_t *info;

    mbedtls_md_init(&ctx);

    info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);

    mbedtls_md_setup(&ctx, info, 1);

    mbedtls_md_hmac_starts(&ctx,
        (unsigned char*)TUYA_DEVICE_SECRET,
        strlen(TUYA_DEVICE_SECRET));

    mbedtls_md_hmac_update(&ctx,
        (unsigned char*)content,
        strlen(content));

    mbedtls_md_hmac_finish(&ctx, hmac);

    mbedtls_md_free(&ctx);

    for(int i=0;i<32;i++)
        sprintf(password + i*2,"%02x",hmac[i]);
}



/********************************************************
                    publish property
********************************************************/

static void tuya_publish_property()
{
    char payload[256];
    long long ts = get_timestamp_ms();
    ESP_LOGI(TAG,"=========> timestamp = %lld",ts);

    sprintf(payload,
    "{"
    "\"msgId\":\"123456\","
    "\"time\":%lld,"
    "\"data\":{"
        "\"switch_led_1\":{"
            "\"value\":true,"
            "\"time\":%lld"
        "}"
    "}"
    "}",
    ts, ts);

    esp_mqtt_client_publish(
            client,
            topic_pub,
            payload,
            0,
            1,
            0);
}



/********************************************************
                    MQTT EVENT
********************************************************/

static void mqtt_event_handler(void *handler_args,
                               esp_event_base_t base,
                               int32_t event_id,
                               void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch(event_id)
    {

        case MQTT_EVENT_CONNECTED:

            ESP_LOGI(TAG,"MQTT CONNECTED");

            esp_mqtt_client_subscribe(client,topic_sub,0);

            ESP_LOGI(TAG,"SUBSCRIBE %s",topic_sub);

            tuya_publish_property();

        break;


        case MQTT_EVENT_DATA:

            ESP_LOGI(TAG,"MQTT DATA");

            printf("TOPIC=%.*s\r\n",
                    event->topic_len,
                    event->topic);

            printf("DATA=%.*s\r\n",
                    event->data_len,
                    event->data);

        break;


        case MQTT_EVENT_DISCONNECTED:

            ESP_LOGW(TAG,"MQTT DISCONNECTED");

        break;

        default:
        break;
    }
}



/********************************************************
                    MQTT START
********************************************************/

void mqtt_app_start(void)
{
    long long ts = get_timestamp_ms();
    ESP_LOGI(TAG,"------>>>>> timestamp = %lld",ts);

    build_username(ts);
    build_password(ts);

    sprintf(clientid,"tuyalink_%s",TUYA_DEVICE_ID);

    sprintf(topic_pub,
        "tylink/%s/thing/property/report",
        TUYA_DEVICE_ID);

    sprintf(topic_sub,
        "tylink/%s/thing/property/set",
        TUYA_DEVICE_ID);

    ESP_LOGI(TAG,"clientid: %s",clientid);
    ESP_LOGI(TAG,"username: %s",username);

    esp_mqtt_client_config_t mqtt_cfg =
    {
        .broker.address.uri = TUYA_BROKER,

        .broker.verification.certificate = (const char *)tuya_root_pem_start,

        .credentials =
        {
            .client_id = clientid,
            .username = username,
            .authentication.password = password,
        },
    };

    client = esp_mqtt_client_init(&mqtt_cfg);

    esp_mqtt_client_register_event(
        client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL);

    esp_mqtt_client_start(client);
}



/********************************************************
                    INIT
********************************************************/

void initial(void)
{
    memset(&MQTT,0,sizeof(MQTT));

    MQTT.Initial          = &initial;
    MQTT.mqttAppStart     = &mqtt_app_start;
    MQTT.mqttEventHandler = &mqtt_event_handler;
}