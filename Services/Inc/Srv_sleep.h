/*
 * Srv_sleep.h
 *
 *  Created on: Jun 12, 2026
 *      Author: Rémi
 */

#ifndef INC_SRV_SLEEP_H_
#define INC_SRV_SLEEP_H_

#include "Station_meteo.h"

void Srv_sleep_init(Station_meteo_t *ctx);
void Srv_sleep_process(Station_meteo_t *ctx);

typedef enum{
	SM_SENSORS_START,
	SM_SENSORS_WAIT
} SM_SENSORS_t;

#endif /* INC_SRV_SLEEP_H_ */
