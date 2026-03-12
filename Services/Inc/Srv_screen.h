/*
 * Srv_screen.h
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#ifndef INC_SRV_SCREEN_H_
#define INC_SRV_SCREEN_H_

#include "Station_meteo.h"

void Srv_screen_init(Station_meteo_t *ctx);
void Srv_screen_process(Station_meteo_t *ctx);

void EPD_test2(void);
void EPD_display_temperature(Station_meteo_t *ctx);

enum{
	SM_SCREEN_START,
	SM_SCREEN_WAIT
};

#endif /* INC_SRV_SCREEN_H_ */
