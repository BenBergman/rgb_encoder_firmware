#include "RgbLedDriver.h"
#include "ws2811_hs.h"

#define LENGTH (uint16_t)16

uint8_t leds[LENGTH][3] = {{0}};

void RgbLedDriver_Create(void)
{
	int i, j;
	for (i = 0; i < LENGTH; i++)
		for (j = 0; j < 3; j++)
			leds[i][j] = 0;
	write_ws2811_hs((uint8_t *)leds, LENGTH * 3, 0);
}

void RgbLedDriver_TurnOn(int led, uint8_t r, uint8_t g, uint8_t b)
{
	leds[led - 1][0] = g;
	leds[led - 1][1] = r;
	leds[led - 1][2] = b;

	write_ws2811_hs((uint8_t *)leds, LENGTH * 3, 0);
}

uint8_t RgbLedDriver_GetLedColour(int led, int colour)
{
	return leds[led - 1][colour];
}
