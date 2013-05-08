#include "LedDriver.h"

enum {
	ALL_LEDS_ON = 0x21,
	ALL_LEDS_OFF = 0x00
};

uint8_t *ledsAddress;

void LedDriver_Create(uint8_t *leds)
{
	ledsAddress = leds;
	*ledsAddress = ALL_LEDS_OFF;
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
	*ledsAddress &= (uint8_t)(~convertLedNumberToBit(led));
}

void LedDriver_TurnAllOn(void)
{
	*ledsAddress |= ALL_LEDS_ON;
}
