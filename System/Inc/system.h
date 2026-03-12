/*
 * system.h
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include "stm32l4xx_hal.h"

uint8_t Scheduler_20ms_Task(void);
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);
void SYS_RTC_Init(Station_meteo_t *ctx);

#endif /* INC_SYSTEM_H_ */
