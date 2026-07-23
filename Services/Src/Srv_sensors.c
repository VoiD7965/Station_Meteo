/*
 * Srv_sensors.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_sensors.h"

SM_SENSORS_t SM_SENSORS;
volatile uint8_t Srv_sensors_flag;
static float temperature, pressure, humidity;
//static float temperature_neg = -10.2f;

void Srv_sensors_init(Station_meteo_t *ctx){
	Srv_sensors_flag = 1;
	SM_SENSORS = SM_SENSORS_START;
}

void Srv_sensors_process(Station_meteo_t *ctx){

	switch(SM_SENSORS){
	case SM_SENSORS_START:
		if(Srv_sensors_flag == 1){
			Srv_sensors_flag = 0;

			BME280_Config(OSRS_2, OSRS_16, OSRS_1, MODE_NORMAL, T_SB_0p5, IIR_16);

			ctx->sleep.sensorsIsReadyToSleep = 0;
			SM_SENSORS = SM_SENSORS_WAIT;
		}
		break;
	case SM_SENSORS_WAIT:
		BME280_Measure(&temperature, &pressure, &humidity);
		temperature = temperature - 1.0f; //todo calibration manuel
	    ctx->sensors.temperature = roundf(temperature * 10.0f) / 10.0f;
	    ctx->sensors.pressure = (uint16_t)roundf(pressure / 100.0f);
	    ctx->sensors.humidity = (uint8_t)roundf(humidity);
	    ctx->sleep.sensorsIsReadyToSleep = 1;

	    BME280_Config(OSRS_2, OSRS_16, OSRS_1, MODE_SLEEP, T_SB_0p5, IIR_16);

	    SM_SENSORS = SM_SENSORS_START;
		break;
	}
}
