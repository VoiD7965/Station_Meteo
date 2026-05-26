/*
 * Srv_battery.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_battery.h"

SM_BATTERY_t SM_BATTERY;
volatile uint8_t Srv_battery_flag;

typedef struct
{
    float voltage;
    uint8_t percent;
} BatteryPoint;

BatteryPoint batteryTable[20] =
{
    {4.20, 100},
    {4.15, 95},
    {4.11, 90},
    {4.08, 85},
    {4.04, 80},
    {4.00, 75},
    {3.96, 70},
    {3.92, 65},
    {3.89, 60},
    {3.85, 55},
    {3.82, 50},
    {3.79, 45},
    {3.77, 40},
    {3.75, 35},
    {3.73, 30},
    {3.70, 25},
    {3.66, 20},
    {3.58, 15},
    {3.45, 10},
    {3.20, 0}
};

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
