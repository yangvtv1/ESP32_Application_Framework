/*
 *              Copyright (c)  2026
 *  File header: 		ext_wifi.h
 *  Created on : 		March 03, 2026
 *      Author : 		R&D Firmware Team (Firmware Developer)
 *      Contact:        hai.luong@gmail.com
 */

#ifndef __EXT_WIFI_H_
#define __EXT_WIFI_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "esp_log.h"
#include "main.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"

extern void ext_wifi_init(void);
extern esp_err_t ext_wifi_connect(const char *ssid, const char *pass);




#endif /* __EXT_WIFI_H_ */
