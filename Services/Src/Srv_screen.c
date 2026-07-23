/*
 * Srv_screen.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_screen.h"
#include "EPD_4in26.h"
#include <stdlib.h>
#include <stdio.h>

SM_SCREEN_t SM_SCREEN;
volatile uint8_t Srv_screen_flag;
UBYTE *BlackImage = NULL;
UDOUBLE Imagesize;

const char* noms_jours[] = {"ERR", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"};

// --- DESSIN DU DÉCOR FIXE ---
static void _draw_static_ui(void)
{
    Paint_DrawLine(20, 65, 780, 65, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 250, 780, 250, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    Paint_DrawLine(20, 440, 780, 440, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    Paint_DrawLine(266, 270, 266, 410, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(533, 270, 533, 410, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    Paint_DrawString_EN(30, 280, "Temperature", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(315, 280, "Pression", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(580, 280, "Humidite", &Font24, BLACK, WHITE);
}

// --- DESSIN DES DONNÉES VARIABLES ---
static void _draw_dynamic_data(Station_meteo_t *ctx)
{
    char buf[32];

    // Date
    uint8_t wd = (ctx->datetime.WeekDay < 8) ? ctx->datetime.WeekDay : 0; //todo inutile de mettre le cas err et de verif ?
    sprintf(buf, "%s %02d/%02d/%04d", noms_jours[wd], ctx->datetime.Day, ctx->datetime.Month, ctx->datetime.Year); //on ecrit dans buf
    Paint_DrawString_EN(20, 20, buf, &Font24, BLACK, WHITE); //on draw buf

    // Batterie
    sprintf(buf, "%d%%", ctx->battery.batterypc);
    Paint_DrawString_EN((ctx->battery.batterypc == 100) ? 613 : (ctx->battery.batterypc >= 10)  ? 630 : 647, 20, buf, &Font24, BLACK, WHITE);
    Paint_DrawRectangle(700, 20, 745, 40, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(745, 26, 750, 34, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(700, 20, 700 + ((45 * ctx->battery.batterypc) / 100), 40, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    // Heure
    sprintf(buf, "%02d:%02d", ctx->datetime.Hour, ctx->datetime.Min);
    Paint_DrawString_EN(225, 125, buf, &Font72, BLACK, WHITE);

    // Capteurs + Unités (pour éviter qu'elles s'effacent)
    sprintf(buf, "%.1f~C", ctx->sensors.temperature);
    Paint_DrawString_EN(30, 340, buf, &Font36, BLACK, WHITE);

    sprintf(buf, "%dhPa", ctx->sensors.pressure);
    Paint_DrawString_EN(275, 340, buf, &Font36, BLACK, WHITE);

    sprintf(buf, "%d%%", ctx->sensors.humidity);
    Paint_DrawString_EN(600, 340, buf, &Font36, BLACK, WHITE);
}

void Srv_screen_init(Station_meteo_t *ctx)
{
    DEV_Module_Init();
    Imagesize = ((EPD_4in26_WIDTH % 8 == 0)? (EPD_4in26_WIDTH / 8 ): (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT;
    if (BlackImage == NULL) BlackImage = (UBYTE *)malloc(Imagesize);

    Paint_NewImage(BlackImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, ROTATE_0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_SetRotate(ROTATE_0);

    EPD_4in26_Init();
    EPD_4in26_Clear();

    Srv_screen_flag = 1;
    SM_SCREEN = SM_SCREEN_WAIT;
}

void Srv_screen_process(Station_meteo_t *ctx)
{
    switch(SM_SCREEN)
    {

    case SM_SCREEN_START:

        if(Srv_screen_flag == 1)
        {
            Srv_screen_flag = 0;

            DEV_Module_Init();

            ctx->sleep.screenIsReadyToSleep = 0;

            SM_SCREEN = SM_SCREEN_WAIT;
        }
        break;

    case SM_SCREEN_WAIT:

        Paint_Clear(WHITE);

        _draw_static_ui();
        _draw_dynamic_data(ctx);

        EPD_4in26_Display_Part(BlackImage, 0, 480, EPD_4in26_WIDTH, 480);

	    //DEV_Module_Exit();
        DEV_Digital_Write(EPD_DC_PIN, 0);
        DEV_Digital_Write(EPD_CS_PIN, 0);
    	DEV_Digital_Write(EPD_PWR_PIN, 0);

        ctx->sleep.screenIsReadyToSleep = 1;

        SM_SCREEN = SM_SCREEN_START;
        break;

    }
}

