#include "LedDriver.h"

uint8_t *ledsAddress;

void LedDriver_Create(uint8_t *leds)
{
	ledsAddress = leds;
	*leds = 0;
}

void LedDriver_TurnOn(int led)
{
	*ledsAddress = 1;
	(void)led;
}

void LedDriver_TurnOff(int led)
{
	*ledsAddress = 0;
	(void)led;
}
