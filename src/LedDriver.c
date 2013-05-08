#include "LedDriver.h"

uint8_t *ledsAddress;

void LedDriver_Create(uint8_t *leds)
{
	ledsAddress = leds;
	*leds = 0;
}

static uint8_t convertLedNumberToBit(int ledNumber)
{
	switch (ledNumber) {
		case 1:
			return 0x01;
		case 2:
			return 0x20;
		default:
			return 0;
	}
}

void LedDriver_TurnOn(int led)
{
	*ledsAddress |= convertLedNumberToBit(led);
}

void LedDriver_TurnOff(int led)
{
	*ledsAddress = 0;
	(void)led;
}
