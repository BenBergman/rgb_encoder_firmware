#include "LedDriver.h"

uint8_t *ledsAddress;

void LedDriver_Create(uint8_t *leds)
{
	ledsAddress = leds;
	*leds = 0;
}

void LedDriver_TurnOn(int led)
{
	switch (led) {
		case 1:
			*ledsAddress ^= 0x01;
			break;
		case 2:
			*ledsAddress ^= 0x20;
			break;
		default:
			break;
	}
}

void LedDriver_TurnOff(int led)
{
	*ledsAddress = 0;
	(void)led;
}
