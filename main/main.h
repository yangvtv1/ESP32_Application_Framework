/*
 *              Copyright (c)  2026
 *  File header: 		mqtt.h
 *  Created on : 		March 03, 2026
 *      Author : 		R&D Firmware Team (Firmware Developer)
 *      Contact:        hai.luong@gmail.com
 */

#ifndef _MAIN_H__
#define _MAIN_H__


#include <stdio.h>
#include <string.h>
#include "ext_mqtt.h"
#include "ext_wifi.h"
#include "nvs_flash.h"
#include "ext_gpio.h"



typedef struct {
    struct{
       void (*mqttAppStart)(void);
    }mqtt;

    struct{
        void (*wifi_init)(void);
        esp_err_t (*wifi_connect)(const char *, const char *);
    }wifi;
    
} application_t;

extern application_t Application;


#endif /* _MAIN_H__ */