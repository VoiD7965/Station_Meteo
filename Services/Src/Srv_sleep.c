/*
 * Srv_sleep.c
 *
 *  Created on: Jun 12, 2026
 *      Author: Rémi
 */

#include "Srv_sensors.h"

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi1;

extern RTC_HandleTypeDef hrtc;

extern ADC_HandleTypeDef hadc1;

void Srv_sleep_init(Station_meteo_t *ctx){

}

void Srv_sleep_process(Station_meteo_t *ctx){

	if (ctx->sleep.batteryIsReadyToSleep == 1 &&
	    ctx->sleep.screenIsReadyToSleep == 1 &&
	    ctx->sleep.sensorsIsReadyToSleep == 1 &&
	    ctx->sleep.timeIsReadyToSleep == 1)
	{


		HAL_SPI_DeInit(&hspi1);
		HAL_I2C_DeInit(&hi2c1);

	    HAL_SuspendTick();
	    HAL_PWREx_EnterSTOP2Mode(PWR_SLEEPENTRY_WFI);

	    SystemClock_Config();
	    HAL_ResumeTick();

	    MX_SPI1_Init();
	    MX_I2C1_Init();


	}

}
