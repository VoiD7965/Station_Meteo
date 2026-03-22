/*
 * system.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "system.h"

extern RTC_HandleTypeDef hrtc;

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

void SYS_RTC_Init(Station_meteo_t *ctx)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  sTime.Hours   = ctx->datetime.Hour;
  sTime.Minutes = ctx->datetime.Min;
  sTime.Seconds = ctx->datetime.Sec;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  sDate.WeekDay = ctx->datetime.WeekDay;
  sDate.Month   = ctx->datetime.Month;
  sDate.Date    = ctx->datetime.Day;
  sDate.Year    = ctx->datetime.Year % 100;
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);

}
