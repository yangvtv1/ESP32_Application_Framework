/*
 *              Copyright (c)  2026
 *  File header: 		ext_ntp.h
 *  Created on : 		March 03, 2026
 *      Author : 		R&D Firmware Team (Firmware Developer)
 *      Contact:        hai.luong@gmail.com
 */

#ifndef __EXT_NTP_H_
#define __EXT_NTP_H_


#include <time.h>
#include <sys/time.h>

#include "esp_sntp.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void ntp_init(void);
void ntp_wait_sync(void);
long long get_timestamp_ms(void);





#endif /* __EXT_NTP_H_ */
