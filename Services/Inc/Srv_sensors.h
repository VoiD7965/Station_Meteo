/*
 * Srv_sensors.h
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#ifndef INC_SRV_SENSORS_H_
#define INC_SRV_SENSORS_H_

#include "Station_meteo.h"
#include "BME280_STM32.h"

void Srv_sensors_init(Station_meteo_t *ctx);
void Srv_sensors_process(Station_meteo_t *ctx);


#endif /* INC_SRV_SENSORS_H_ */
