/*
 * Srv_time.c
 * Logic: RTC remains in Standard Time (Winter).
 * Display is adjusted (+1h) during Summer.
 */

#include "Srv_time.h"

uint8_t SM_TIME;
volatile uint8_t Srv_time_flag;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;

static int isSummerTime(uint8_t d, uint8_t m, uint8_t y, uint8_t h, uint8_t wd) {

    if (m < 3 || m > 10) return 0;
    if (m > 3 && m < 10) return 1;

    int sundayDate = d + (7 - wd);

    // --- CAS DE MARS ---
    if (m == 3) {
        if (sundayDate <= 31) {
            if (d < sundayDate) return 0;
            if (d == sundayDate) return (h >= 2);
        }
        return 1;
    }

    // --- CAS D'OCTOBRE ---
    if (m == 10) {
        if (sundayDate <= 31) {
            if (d < sundayDate) return 1;
            if (d == sundayDate) return (h < 2);
        }
        return 0;
    }

    return 0;
}

void Srv_time_init(Station_meteo_t *ctx){
	Srv_time_flag = 1;
	SM_TIME = SM_TIME_START;
}

void Srv_time_process(Station_meteo_t *ctx){

	switch(SM_TIME){
		case SM_TIME_START:
			if(Srv_time_flag == 1){
				Srv_time_flag = 0;

				// 1. Lecture de l'heure brute (RTC Matériel)
				HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

				// 2. Calcul de l'heure d'affichage
				uint8_t displayHour = sTime.Hours;
				uint8_t displayDay  = sDate.Date;

				if (isSummerTime(sDate.Date, sDate.Month, sDate.Year, sTime.Hours, sDate.WeekDay)) {
					displayHour += 1;
					if (displayHour >= 24) {
						displayHour = 0;
					}
				}

				// 3. Mise à jour du contexte (ce qui sera affiché sur l'écran)
				ctx->datetime.Sec      = sTime.Seconds;
				ctx->datetime.Min      = sTime.Minutes;
				ctx->datetime.Hour     = displayHour; // Valeur modifiée
				ctx->datetime.Day      = displayDay;
				ctx->datetime.Month    = sDate.Month;
				ctx->datetime.Year     = 2000 + sDate.Year;
				ctx->datetime.WeekDay  = sDate.WeekDay;

				SM_TIME = SM_TIME_WAIT;
			}
			break;

		case SM_TIME_WAIT:
			// Le flag sera remis à 1 par ton scheduler ou la boucle
			SM_TIME = SM_TIME_START;
			break;
	}
}
