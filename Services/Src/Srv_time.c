/*
 * Srv_time.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_time.h"

uint8_t SM_TIME;
volatile uint8_t Srv_time_flag;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;

void Srv_time_init(Station_meteo_t *ctx){
	Srv_time_flag = 1;
	SM_TIME = SM_TIME_START;
}

void Srv_time_process(Station_meteo_t *ctx){

	switch(SM_TIME){
	case SM_TIME_START:
		if(Srv_time_flag == 1){
			Srv_time_flag = 0;

			HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		    ctx->datetime.Sec  = sTime.Seconds;
		    ctx->datetime.Min  = sTime.Minutes;
		    ctx->datetime.Hour = sTime.Hours;
		    ctx->datetime.Day   = sDate.Date;
		    ctx->datetime.Month = sDate.Month;
		    ctx->datetime.Year  = 2000 + sDate.Year;

			SM_TIME =SM_TIME_WAIT;
		}
		break;
	case SM_TIME_WAIT:

		SM_TIME =SM_TIME_START;
		break;
	}

}
