#include "RgbLedDriver.h"
#include "ws2811_hs.h"

#define LENGTH (uint16_t)16

void RgbLedDriver_Create(void)
{
	uint8_t leds[LENGTH][3] = {{0}};
	uint8_t pinmask = 0;
	write_ws2811_hs((uint8_t *)leds, LENGTH * 3, pinmask);
}
