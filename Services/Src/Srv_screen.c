/*
 * Srv_screen.c
 *
 *  Created on: Mar 6, 2026
 *      Author: Rémi
 */

#include "Srv_screen.h"

#include "EPD_Test.h"
#include "EPD_4in26.h"
#include <time.h>

uint8_t SM_SCREEN;
volatile uint8_t Srv_screen_flag;
UBYTE *BlackImage;
UDOUBLE Imagesize;

void Srv_screen_init(Station_meteo_t *ctx)
{

	DEV_Module_Init();
    EPD_4in26_Init();
    EPD_4in26_Clear();
    //DEV_Delay_ms(500);

    Imagesize = ((EPD_4in26_WIDTH % 8 == 0)? (EPD_4in26_WIDTH / 8 ): (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT;
    BlackImage = (UBYTE *)malloc(Imagesize);
    Paint_NewImage(BlackImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    Srv_screen_flag = 1;
    SM_SCREEN = SM_SCREEN_START;
}

void Srv_screen_process(Station_meteo_t *ctx)
{

    switch(SM_SCREEN)
    {
        case SM_SCREEN_START:

            if(Srv_screen_flag == 1)
            {
                Srv_screen_flag = 0;

                Paint_Clear(WHITE);
                Paint_DrawDate(20, 20, &ctx->datetime, &Font24, WHITE, BLACK);
                // Dessin icone batterie : Corps (x1, y1, x2, y2)
                Paint_DrawRectangle(655, 22, 700, 42, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
                Paint_DrawRectangle(700, 28, 705, 36, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                //Paint_DrawDate(710, 20, & ctx->battery, &Font24, WHITE, BLACK);

                // Ligne horizontale sous le header
                Paint_DrawLine(20, 65, 780, 65, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

                Paint_DrawTime(145, 110, &ctx->datetime, &Font72, WHITE, BLACK);

                // Ligne horizontale sous l'heure
                Paint_DrawLine(20, 250, 780, 250, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

                /* -------- TEMPERATURE -------- */
                Paint_DrawString_EN(30, 280, " Temperature", &Font24, BLACK, WHITE);
                Paint_DrawNumDecimals(95, 340, ctx->sensors.temperature, &Font24, 1, WHITE, BLACK);      // xx.x
                Paint_DrawString_EN(170, 340, "C", &Font24, BLACK, WHITE);           // unité

                // Séparateur vertical 1
                Paint_DrawLine(266, 270, 266, 410, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

                /* -------- PRESSION -------- */

                Paint_DrawString_EN(315, 280, " Pression", &Font24, BLACK, WHITE);
                Paint_DrawNumDecimals(345, 340, ctx->sensors.pressure, &Font24, 0, WHITE, BLACK);      // xxxx
                Paint_DrawString_EN(390, 340, " hPa", &Font24, BLACK, WHITE);           // unité
                // Séparateur vertical 2
                Paint_DrawLine(533, 270, 533, 410, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

                /* -------- HUMIDITE -------- */

                Paint_DrawString_EN(580, 280, " Humidite", &Font24, BLACK, WHITE);
                Paint_DrawNumDecimals(635, 340, ctx->sensors.humidity, &Font24, 0, WHITE, BLACK);      // xx
                Paint_DrawString_EN(665, 340, " %", &Font24, BLACK, WHITE);           // unité
                // Ligne de finition tout en bas
                Paint_DrawLine(20, 440, 780, 440, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

                EPD_4in26_Display_Part(BlackImage, 0, 480, EPD_4in26_WIDTH, 480);

                SM_SCREEN = SM_SCREEN_WAIT;
            }
            break;

        case SM_SCREEN_WAIT:
            SM_SCREEN = SM_SCREEN_START;
            break;
    }
}

void EPD_display_temperature(Station_meteo_t *ctx)
{
    static UBYTE *BlackImage;
    static int init_done = 0;
    char text[16];

    if (!init_done)
    {
        DEV_Module_Init();

        EPD_4in26_Init();
        EPD_4in26_Clear();

        UDOUBLE Imagesize = ((EPD_4in26_WIDTH % 8 == 0) ? (EPD_4in26_WIDTH / 8) : (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT;

        BlackImage = (UBYTE *)malloc(Imagesize);

        Paint_NewImage(BlackImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, 0, WHITE);

        init_done = 1;
    }

    /* format temperature */
    sprintf(text, "%.1f C", ctx->sensors.temperature); //Miscellaneous : -u _printf_float

    /* draw */
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    Paint_DrawString_EN(20, 100, text, &Font24, BLACK, WHITE);

    EPD_4in26_Display_Base(BlackImage);

    DEV_Delay_ms(1000);
}

void EPD_test2()
{
    UBYTE *BlackImage;
    UDOUBLE Imagesize;

    DEV_Module_Init();

    EPD_4in26_Init();
    EPD_4in26_Clear();

    Imagesize = ((EPD_4in26_WIDTH % 8 == 0) ? (EPD_4in26_WIDTH / 8) : (EPD_4in26_WIDTH / 8 + 1)) * EPD_4in26_HEIGHT;

    BlackImage = (UBYTE *)malloc(Imagesize);

    Paint_NewImage(BlackImage, EPD_4in26_WIDTH, EPD_4in26_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

}
