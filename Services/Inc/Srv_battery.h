/*
 * Srv_battery.h
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#ifndef INC_SRV_BATTERY_H_
#define INC_SRV_BATTERY_H_

#include "Station_meteo.h"

void Srv_battery_init(Station_meteo_t *ctx);
void Srv_battery_process(Station_meteo_t *ctx);
uint8_t Battery_ADCToPercentage(uint32_t adc);

typedef enum{
	SM_BATTERY_START,
	SM_BATTERY_MEASURE
} SM_BATTERY_t;

#endif /* INC_SRV_BATTERY_H_ */
