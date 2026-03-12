/*
 * Srv_time.h
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#ifndef INC_SRV_TIME_H_
#define INC_SRV_TIME_H_

#include "Station_meteo.h"

void Srv_screen_init(Station_meteo_t *ctx);
void Srv_screen_process(Station_meteo_t *ctx);

enum{
	SM_TIME_START,
	SM_TIME_WAIT
};

#endif /* INC_SRV_TIME_H_ */
