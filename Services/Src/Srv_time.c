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

/**
 * @brief Calcule si nous sommes en heure d'été (Europe)
 * Règle : Dernier dimanche de mars (2h) au dernier dimanche d'octobre (3h)
 */
static int isSummerTime(uint8_t d, uint8_t m, uint8_t y, uint8_t h, uint8_t wd) {
    // Janvier, Février, Novembre, Décembre -> Hiver (0)
    if (m < 3 || m > 10) return 0;
    // Avril à Septembre -> Été (1)
    if (m > 3 && m < 10) return 1;

    // wd : 1=Lundi, ..., 7=Dimanche (Format STM32)
    // On calcule la date du dimanche de la semaine actuelle
    // Exemple : si on est le samedi 30 mars (wd=6), le dimanche est le 30 + (7-6) = 31.
    int sundayDate = d + (7 - wd);

    // --- CAS DE MARS ---
    if (m == 3) {
        // Si le dimanche de cette semaine est encore en mars (<= 31)
        if (sundayDate <= 31) {
            if (d < sundayDate) return 0; // On est entre lundi et samedi avant le dernier dimanche
            if (d == sundayDate) return (h >= 2); // On est le dimanche, on attend 2h
        }
        // Si le dimanche de cette semaine est déjà en avril, le dernier dimanche de mars est passé
        return 1;
    }

    // --- CAS D'OCTOBRE ---
    if (m == 10) {
        // Si le dimanche de cette semaine est encore en octobre (<= 31)
        if (sundayDate <= 31) {
            if (d < sundayDate) return 1; // On est entre lundi et samedi avant le dernier dimanche
            if (d == sundayDate) return (h < 2); // On est le dimanche, on repasse en hiver à 2h
        }
        // Si le dimanche de cette semaine est déjà en novembre, le dernier dimanche d'octobre est passé
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

            // On n'applique le décalage que si l'année est réglée (sécurité)
            if (sDate.Year >= 24) {
                if (isSummerTime(sDate.Date, sDate.Month, sDate.Year, sTime.Hours, sDate.WeekDay)) {
                    displayHour += 1;

                    // Si il est 23h et qu'on ajoute 1h, on passe à 00h
                    if (displayHour >= 24) {
                        displayHour = 0;
                        // On pourrait incrémenter le jour ici, mais pour une station météo
                        // l'heure est le plus critique.
                    }
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
