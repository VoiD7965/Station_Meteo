/*
 * Station_meteo.c
 *
 *  Created on: Mar 5, 2026
 *      Author: Rémi
 */

#include "Station_meteo.h"

void Station_meteo_init(Station_meteo_t *ctx)
{
    ctx->sensors.temperature = 0;
    ctx->sensors.humidity = 0;
    ctx->sensors.pressure = 0;

    ctx->datetime.Sec = 0x45;
    ctx->datetime.Min = 0x59;
    ctx->datetime.Hour = 0x23;
    ctx->datetime.Day = 0x12;
    ctx->datetime.Month = 0x03;
    ctx->datetime.Year = 0x26;
    ctx->datetime.WeekDay = 0x04;

    ctx->battery.batterypc = 25;

    SYS_RTC_Init(ctx);

	Srv_sensors_init(ctx);
//	Srv_battery_init(ctx);
	Srv_time_init(ctx);
	Srv_screen_init(ctx);
}

void Station_meteo_process(Station_meteo_t *ctx)
{
	if(Scheduler_20ms_Task()){
		//input
		Srv_sensors_process(ctx);
		//Srv_battery_process(ctx);

		//process
		Srv_time_process(ctx);

		//output
		Srv_screen_process(ctx);
	}
}
