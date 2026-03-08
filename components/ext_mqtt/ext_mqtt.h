/*
 *              Copyright (c)  2026
 *  File header: 		ext_mqtt.h
 *  Created on : 		March 03, 2026
 *      Author : 		R&D Firmware Team (Firmware Developer)
 *      Contact:        hai.luong@gmail.com
 */

#ifndef __EXT_MQTT_H_
#define __EXT_MQTT_H_


#include <stdio.h>
#include <stdint.h>
#include "esp_event.h"
#include <string.h>
#include "mqtt_client.h"
#include "esp_log.h"



typedef struct{
    void (*Initial)(void);
    void (*mqttAppStart)(void);
    void (*mqttEventHandler)(void *, esp_event_base_t , int32_t , void *);

}ext_mqtt_t;

extern ext_mqtt_t MQTT;
extern void initial(void);
extern void mqtt_app_start(void);



#endif /* __EXT_MQTT_H_ */
