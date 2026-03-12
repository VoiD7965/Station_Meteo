/*
 * system.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "system.h"

RTC_AlarmTypeDef sAlarm = {0};

static uint32_t last_tick_20ms = 0;
extern volatile uint8_t Srv_battery_flag;
extern volatile uint8_t Srv_screen_flag;
extern volatile uint8_t Srv_sensors_flag;
extern volatile uint8_t Srv_time_flag;

uint8_t Scheduler_20ms_Task(void)
{
    uint32_t appTick = HAL_GetTick();

    if ((appTick - last_tick_20ms) >= 20)
    {
        last_tick_20ms = appTick;
        return 1;
    }
    return 0;
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	Srv_battery_flag = 1;
	Srv_screen_flag = 1;
	Srv_sensors_flag = 1;
	Srv_time_flag = 1;
	//HAL_RTCEx_SetWakeUpTimer(hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
}
