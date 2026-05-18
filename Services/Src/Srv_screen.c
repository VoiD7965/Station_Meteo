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

uint8_t SM_SCREEN;
volatile uint8_t Srv_screen_flag;
UBYTE *BlackImage = NULL;
UDOUBLE Imagesize;

static int last_minute = -1;
static int last_hour = -1;

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
    const char* noms_jours[] = {"ERR", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam", "Dim"};
    uint8_t wd = (ctx->datetime.WeekDay < 8) ? ctx->datetime.WeekDay : 0;
    sprintf(buf, "%s %02d/%02d/%04d", noms_jours[wd], ctx->datetime.Day, ctx->datetime.Month, (int)ctx->datetime.Year + 2000);
    Paint_DrawString_EN(20, 20, buf, &Font24, BLACK, WHITE);

    // Batterie
    sprintf(buf, "%d%%", ctx->battery.batterypc);
    Paint_DrawString_EN(640, 20, buf, &Font24, BLACK, WHITE);
    Paint_DrawRectangle(700, 22, 745, 42, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(745, 28, 750, 36, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    int remplissage = (41 * ctx->battery.batterypc) / 100;
    Paint_DrawRectangle(702, 24, 702 + remplissage, 40, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    // Heure
    sprintf(buf, "%02d:%02d", ctx->datetime.Hour, ctx->datetime.Min);
    Paint_DrawString_EN(280, 110, buf, &Font72, BLACK, WHITE);

    // Capteurs + Unités (pour éviter qu'elles s'effacent)
    sprintf(buf, "%.1f ~C", ctx->sensors.temperature);
    Paint_DrawString_EN(30, 340, buf, &Font36, BLACK, WHITE);

    sprintf(buf, "%d hPa", (int)ctx->sensors.pressure);
    Paint_DrawString_EN(275, 340, buf, &Font36, BLACK, WHITE);

    sprintf(buf, "%d %%", (int)ctx->sensors.humidity);
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
        case SM_SCREEN_WAIT:
            if (ctx->datetime.Hour != last_hour || Srv_screen_flag == 1)
                SM_SCREEN = SM_SCREEN_HOURLY;
            else if (ctx->datetime.Min != last_minute)
                SM_SCREEN = SM_SCREEN_PARTIAL;
            break;

        case SM_SCREEN_HOURLY:
            EPD_4in26_Init(); // FULL INIT (Reset physique + Flash noir)
            Paint_Clear(WHITE);
            _draw_static_ui();
            _draw_dynamic_data(ctx);
            EPD_4in26_Display_Base(BlackImage);

            last_hour = ctx->datetime.Hour;
            last_minute = ctx->datetime.Min;
            Srv_screen_flag = 0;
            SM_SCREEN = SM_SCREEN_WAIT;
            break;

        case SM_SCREEN_PARTIAL:
            // --- GOMMAGE DE LA RAM (Rectangles blancs) ---
            Paint_DrawRectangle(0, 0, 800, 63, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);      // Header
            Paint_DrawRectangle(0, 67, 800, 248, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);    // Heure
            Paint_DrawRectangle(25, 330, 250, 410, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);  // Temp
            Paint_DrawRectangle(270, 330, 530, 410, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); // Press
            Paint_DrawRectangle(540, 330, 780, 410, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL); // Humid

            _draw_dynamic_data(ctx);

            // On n'appelle PAS Init_Partial si on n'utilise pas le Sleep
            // On envoie directement les données avec la fonction sans flash
            EPD_4in26_Display_Partial_True(BlackImage);

            last_minute = ctx->datetime.Min;
            SM_SCREEN = SM_SCREEN_WAIT;
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
