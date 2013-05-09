#include "LedDriver.h"

static const uint8_t ALL_LEDS_ON = 0x41;

uint8_t *ledsAddress;

void LedDriver_Create(uint8_t *leds)
{
	ledsAddress = leds;
	*ledsAddress = 0;
}

static uint8_t convertLedNumberToBit(int ledNumber)
{
	switch (ledNumber) {
		case 1:
			return 0x01;
		case 2:
			return 0x40;
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

void LedDriver_TurnAllOff(void)
{
	*ledsAddress &= (uint8_t)(~ALL_LEDS_ON);
}
