/*
 * Srv_battery.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_battery.h"

SM_BATTERY_t SM_BATTERY;
volatile uint8_t Srv_battery_flag;
extern ADC_HandleTypeDef hadc1;

#define MAX_INDEX 1
static uint32_t value;
static uint8_t index = 0;
static uint32_t pc[MAX_INDEX];

uint32_t t1 = 0;
uint32_t t2 = 0;

typedef struct
{
    float voltage;
    uint8_t percent;
} BatteryPoint;

/* =========================
   Configuration hardware
   ========================= */

/* Gain du pont diviseur */
#define ADC_DIVIDER_GAIN       1.303f

/* Référence ADC */
#define ADC_VREF               3.300f

/* ADC 12 bits STM32 */
#define ADC_MAX                4095.0f

/* =========================
   Lookup table batterie
   (vraie tension cellule)
   ========================= */

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

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

	SM_BATTERY = SM_BATTERY_START;
}

void Srv_battery_process(Station_meteo_t *ctx){

	switch(SM_BATTERY){
	case SM_BATTERY_START:
		if(Srv_battery_flag == 1){
			Srv_battery_flag = 0;
			ctx->sleep.batteryIsReadyToSleep = 0;

			SM_BATTERY = SM_BATTERY_MEASURE;
		}
		break;

	case SM_BATTERY_MEASURE:

		HAL_GPIO_WritePin(CMD_BAT_MEAS_GPIO_Port, CMD_BAT_MEAS_Pin, GPIO_PIN_SET);

		HAL_ADC_Start(&hadc1);

		HAL_ADC_PollForConversion(&hadc1, 100);

		value = HAL_ADC_GetValue(&hadc1);

		HAL_ADC_Stop(&hadc1);

		HAL_GPIO_WritePin(CMD_BAT_MEAS_GPIO_Port, CMD_BAT_MEAS_Pin, GPIO_PIN_RESET);

		pc[index] = Battery_ADCToPercentage(value);

		index++;

		if(index >= MAX_INDEX)
		{
			index = 0;
		}

		bool all_equal = true;

		for (int i = 1; i < MAX_INDEX; i++)
		{
		    if (pc[i] != pc[0])
		    {
		    	all_equal = false;
		        break;
		    }
		}

		if (all_equal)
		{
			ctx->battery.batterypc = pc[0];

		}

		ctx->sleep.batteryIsReadyToSleep = 1;
		SM_BATTERY = SM_BATTERY_START;

		break;

	}

}

uint8_t Battery_ADCToPercentage(uint32_t adc)
{
    float adcVoltage;
    float batteryVoltage;
    uint8_t batteryPercentage;
    uint8_t i;

    /* Conversion ADC -> tension ADC */
    adcVoltage = ((float)adc * ADC_VREF) / ADC_MAX;

    /* Compensation pont diviseur
       ADC_DIVIDER_GAIN est déjà inversé */
    batteryVoltage = adcVoltage * ADC_DIVIDER_GAIN;

    /* Saturation haute */
    if (batteryVoltage >= batteryTable[0].voltage)
    {
        return 100;
    }

    /* Saturation basse */
    if (batteryVoltage <= batteryTable[19].voltage)
    {
        return 0;
    }

    /* Recherche dans la LUT */
    for (i = 0; i < 19; i++)
    {
        float vHigh = batteryTable[i].voltage;
        float vLow  = batteryTable[i + 1].voltage;

        uint8_t pHigh = batteryTable[i].percent;
        uint8_t pLow  = batteryTable[i + 1].percent;

        /* Tension trouvée dans l'intervalle */
        if ((batteryVoltage <= vHigh) && (batteryVoltage >= vLow))
        {
            float ratio;

            /* Interpolation linéaire */
            ratio = (batteryVoltage - vLow) / (vHigh - vLow);

            batteryPercentage = pLow + (uint8_t)((pHigh - pLow) * ratio);

            return batteryPercentage;
        }
    }

    return 0;
}
