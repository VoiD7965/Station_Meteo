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

void Srv_screen_init(Station_meteo_t *ctx){

}

void Srv_screen_process(Station_meteo_t *ctx){
	//EPD_test2();
	EPD_test();
	//EPD_display_temperature(ctx);
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
