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
                Paint_DrawTime(0, 0, &ctx->datetime, &Font72, WHITE, BLACK);
                Paint_DrawDate(0, 100, &ctx->datetime, &Font72, WHITE, BLACK);

                /* -------- TEMPERATURE -------- */

                Paint_DrawNumDecimals(0, 220, ctx->sensors.temperature, &Font24, 1, WHITE, BLACK);      // xx.x
                Paint_DrawString_EN(50, 220, " C", &Font24, BLACK, WHITE);           // unité

                /* -------- HUMIDITE -------- */
                Paint_DrawNumDecimals(200, 220, ctx->sensors.humidity, &Font24, 0, WHITE, BLACK);      // xx
                Paint_DrawString_EN(250, 220, " %", &Font24, BLACK, WHITE);           // unité

                /* -------- PRESSION -------- */
                Paint_DrawNumDecimals(400, 220, ctx->sensors.pressure, &Font24, 0, WHITE, BLACK);      // xxxx
                Paint_DrawString_EN(450, 220, " hPa", &Font24, BLACK, WHITE);           // unité

                Paint_DrawString_EN(0, 250, "THEO LE CACA", &Font72, BLACK, WHITE);

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
