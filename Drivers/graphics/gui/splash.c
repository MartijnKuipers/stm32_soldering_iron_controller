/*
 * splash.c
 *
 *  Created on: Aug 7, 2017
 *      Author: jose
 */

#include "splash.h"
#define SPLASH_TIMEOUT 1000

static int splash_processInput(screen_t * scr, RE_Rotation_t input, RE_State_t *);
static void splash_init(screen_t * scr);
static void splash_draw(screen_t * scr);

static uint32_t splash_time;
void splash_setup(screen_t * scr) {

	scr->processInput = &splash_processInput;
	scr->init = &splash_init;
	scr->draw = &splash_draw;
	scr->update = NULL;
}

static int splash_processInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state) {
	if(HAL_GetTick() - splash_time > SPLASH_TIMEOUT)
		return screen_main;
	return -1;
}

static unsigned char logo [] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x60, 0xF0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0xFC, 0xFC, 0xFC, 0x5C, 0x44,
		0x44, 0xE4, 0xFC, 0xFC, 0xBF, 0x1F, 0x07, 0x0F, 0x1F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
		0xFC, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x04, 0x84, 0xFC, 0xFC, 0xFC, 0x3C, 0x04, 0x04, 0x04,
		0x80, 0xE0, 0xE0, 0xE0, 0x20, 0x20, 0x20, 0xE0, 0xE0, 0xE0, 0x00, 0x80, 0xE0, 0xE0, 0x60, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x00, 0xE0, 0xFC, 0xFC, 0x3C, 0x24, 0x20, 0xA0, 0xE0, 0xE0, 0x40, 0x00,
		0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0F,
		0x0F, 0x8F, 0x0B, 0x08, 0x08, 0x0E, 0x8F, 0xCF, 0xEF, 0xF3, 0xF8, 0xFC, 0xFE, 0xFF, 0x7F, 0x3F,
		0x1F, 0x8F, 0xCF, 0xE7, 0x73, 0x39, 0x1C, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x0F,
		0x07, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x01, 0x00,
		0x0F, 0x0F, 0x0F, 0x09, 0x08, 0x08, 0x08, 0x00, 0x00, 0x0E, 0x0F, 0x0F, 0x01, 0x00, 0x00, 0x08,
		0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x38,
		0x60, 0xC0, 0xC8, 0x9C, 0x3E, 0x7F, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0x7F, 0x7F, 0x3F, 0x9F, 0xCF,
		0xE7, 0x73, 0x39, 0x1C, 0x0E, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x39, 0x63, 0x73, 0x38,
		0x1C, 0x0E, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		};
static UG_BMP bmp;

static void splash_init(screen_t * scr) {
	splash_time = HAL_GetTick();
	bmp.p = logo;
	bmp.width = 85;
	bmp.height = 48;
	bmp.colors = 2;
	bmp.bpp = 8;
}

static void splash_draw(screen_t * scr) {
	  UG_DrawBMP(22,15, &bmp);
}