/*
 * App.h
 *
 *  Created on: Mar 5, 2026
 *      Author: Rémi
 */

#ifndef INC_STATION_METEO_H_
#define INC_STATION_METEO_H_

typedef struct
{
	float temperature;
	uint16_t pressure;
	uint8_t humidity;

} sensors_t;

typedef struct
{
	uint8_t secondes; //todo tbd
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;

} datetime_t;

typedef struct
{
	uint8_t batterypc;

} battery_t;

typedef struct
{
    sensors_t sensors;
    datetime_t datetime;
    battery_t battery;

} Station_meteo_t;

//ctx = variable contexte
void Station_meteo_init(Station_meteo_t *ctx);
void Station_meteo_process(Station_meteo_t *ctx);

#endif /* INC_STATION_METEO_H_ */
