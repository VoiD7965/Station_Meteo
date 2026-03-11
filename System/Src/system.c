/*
 * system.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "system.h"

static uint32_t last_tick_20ms = 0;

uint8_t Scheduler_20ms_Task(void)
{
    uint32_t appTick = HAL_GetTick();

    if ((appTick - last_tick_20ms) >= 20)
    {
        last_tick_20ms = appTick;
        return 1;
    }
    return 0;
}
