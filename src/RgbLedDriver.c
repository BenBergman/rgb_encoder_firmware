#include "RgbLedDriver.h"

/* This function is defined in the associated .S assembly source file */
void write_ws2811_hs(uint8_t *data, uint16_t length, uint8_t pinmask);

#define LENGTH (uint16_t)16

uint8_t leds[LENGTH][COLOURS_TOTAL] = {{0}};

void RgbLedDriver_Create(void)
{
	int i, j;
	for (i = 0; i < LENGTH; i++)
		for (j = 0; j < COLOURS_TOTAL; j++)
			leds[i][j] = 0;
	write_ws2811_hs((uint8_t *)leds, LENGTH * COLOURS_TOTAL, 0);
}

void RgbLedDriver_TurnOn(int led, uint8_t r, uint8_t g, uint8_t b)
{
	leds[led - 1][RED] = r;
	leds[led - 1][GREEN] = g;
	leds[led - 1][BLUE] = b;

	write_ws2811_hs((uint8_t *)leds, LENGTH * COLOURS_TOTAL, 0);
}

uint8_t RgbLedDriver_GetLedColour(int led, int colour)
{
	return leds[led - 1][colour];
}
