/*
 * Srv_sensors.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_sensors.h"

static float temperature, pressure, humidity;
static float temperaturet = -10.2f;

void Srv_sensors_init(Station_meteo_t *ctx){
	if(BME280_Config(OSRS_2, OSRS_16, OSRS_1, MODE_NORMAL, T_SB_0p5, IIR_16) != 0){
		Error_Handler();
	}
}

void Srv_sensors_process(Station_meteo_t *ctx){
	BME280_Measure(&temperature, &pressure, &humidity);

    ctx->sensors.temperature = roundf(temperature * 10.0f) / 10.0f;
    ctx->sensors.pressure = (uint16_t)roundf(pressure / 100.0f);
    ctx->sensors.humidity = (uint8_t)roundf(humidity);

}
