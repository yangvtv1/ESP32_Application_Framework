#include "ext_ntp.h"

static const char *TAG = "ext_ntp";

void ntp_init(void)
{
    ESP_LOGI(TAG,"init ntp");

    sntp_setoperatingmode(SNTP_OPMODE_POLL);

    sntp_setservername(0,"pool.ntp.org");
    sntp_setservername(1,"time.google.com");

    sntp_init();
}

void ntp_wait_sync(void)
{
    time_t now = 0;
    struct tm timeinfo = {0};

    int retry = 0;

    while(timeinfo.tm_year < (2024 - 1900) && retry < 15)
    {
        ESP_LOGI(TAG,"waiting time sync...");

        vTaskDelay(2000 / portTICK_PERIOD_MS);

        time(&now);
        localtime_r(&now,&timeinfo);

        retry++;
    }

    ESP_LOGI(TAG,"time synced");
}

long long get_timestamp_ms()
{
    struct timeval tv;

    gettimeofday(&tv,NULL);

    return ((long long)tv.tv_sec * 1000LL + tv.tv_usec/1000);
}