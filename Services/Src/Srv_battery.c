/*
 * Srv_battery.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_battery.h"

uint8_t SM_BATTERY;
volatile uint8_t Srv_battery_flag;

void Srv_battery_init(Station_meteo_t *ctx){
	Srv_battery_flag = 1;
	SM_BATTERY = SM_BATTERY_START;
}

void Srv_battery_process(Station_meteo_t *ctx){

	switch(SM_BATTERY){
	case SM_BATTERY_START:
		if(Srv_battery_flag == 1){
			Srv_battery_flag = 0;
			SM_BATTERY = SM_BATTERY_WAIT;
		}
		break;
	case SM_BATTERY_WAIT:
		SM_BATTERY = SM_BATTERY_START;
		break;
	}

}
