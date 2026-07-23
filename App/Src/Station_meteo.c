/*
 * Station_meteo.c
 *
 *  Created on: Mar 5, 2026
 *      Author: Rémi
 */

#include "Station_meteo.h"

extern RTC_HandleTypeDef hrtc;

void Station_meteo_init(Station_meteo_t *ctx)
{

    ctx->sensors.temperature = 0;
    ctx->sensors.humidity = 0;
    ctx->sensors.pressure = 0;

    ctx->datetime.Sec = BUILD_SEC;
    ctx->datetime.Min = BUILD_MIN;
    ctx->datetime.Hour = BUILD_HOUR;
    ctx->datetime.Day = BUILD_DAY;
    ctx->datetime.WeekDay = BUILD_WEEKDAY; //RTC_WEEKDAY_SUNDAY
    ctx->datetime.Month = BUILD_MONTH;
    ctx->datetime.Year = BUILD_YEAR;
    ctx->datetime.DST = BUILD_DST; // 1 = heure d'été, 0 = heure d'hiver

    ctx->battery.batterypc = 0;

    ctx->sleep.batteryIsReadyToSleep = 0;
    ctx->sleep.screenIsReadyToSleep = 0;
    ctx->sleep.sensorsIsReadyToSleep = 0;
    ctx->sleep.timeIsReadyToSleep = 0;

    SYS_RTC_Init(ctx);

    //calibration
    //HAL_RTCEx_SetSmoothCalib(&hrtc, RTC_SMOOTHCALIB_PERIOD_32SEC, RTC_SMOOTHCALIB_PLUSPULSES_RESET, 0); //todo
    HAL_RTCEx_SetSmoothCalib(
        &hrtc,
        RTC_SMOOTHCALIB_PERIOD_32SEC,
        RTC_SMOOTHCALIB_PLUSPULSES_RESET,  // CP = 0
        97                                // CM = 97
    );

    if(ctx->datetime.DST)
    {
    	HAL_RTC_DST_SetStoreOperation(&hrtc); 		//flash à l'heure d'été
    }
    else
    {
    	HAL_RTC_DST_ClearStoreOperation(&hrtc);		//flash à l'heure d'hiver
    }

	Srv_sensors_init(ctx);
	Srv_battery_init(ctx);
	Srv_time_init(ctx);
	Srv_screen_init(ctx);
	Srv_sleep_init(ctx);
}


void Station_meteo_process(Station_meteo_t *ctx)
{
	if(Scheduler_20ms_Task()){

		//input
		Srv_sensors_process(ctx);
		Srv_battery_process(ctx);

		//process
		Srv_time_process(ctx);

		//output
		Srv_screen_process(ctx);

		Srv_sleep_process(ctx);

	}
}
