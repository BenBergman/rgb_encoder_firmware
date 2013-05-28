//#include <msp430g2553.h>   /* Genericizable */
#include <msp430.h>
#include "RgbLedDriver.h"
#include "RotaryEncoder.h"

#define pin6mask  (0x01 << 6)

int main(void) {
	/* Hold the watchdog timer so it doesn't reset our chip */
	WDTCTL = WDTPW + WDTHOLD;
	_BIS_SR(OSCOFF);                          // XTAL not used
	if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)
	{
		/* If calibration constants erased
		 * do not load, trap CPU!!
		 */
		while(1);
	}
	BCSCTL1 = CALBC1_16MHZ;  // Set DCO to 16MHz
	DCOCTL = CALDCO_16MHZ;

	P1DIR = 0x01;
	P2DIR &= ~(0b11000000);
	P2REN |= 0b11000000;

	RgbLedDriver_Create();
	RotaryEncoder_Create((uint8_t *)(&P2IN), 6, 7);

	int i = 0;
	/* infinite loop */
	for( ; ; ) {
		/*
		RgbLedDriver_TurnOn((i + 1 ) % 16 + 1, 5, 1, 1);
		RgbLedDriver_TurnOn((i + 2 ) % 16 + 1, 1, 5, 1);
		RgbLedDriver_TurnOn((i + 3 ) % 16 + 1, 1, 1, 5);
		RgbLedDriver_TurnOn((i + 4 ) % 16 + 1, 5, 5, 5);
		RgbLedDriver_TurnOn((i + 5 ) % 16 + 1, 5, 1, 1);
		RgbLedDriver_TurnOn((i + 6 ) % 16 + 1, 1, 5, 1);
		RgbLedDriver_TurnOn((i + 7 ) % 16 + 1, 1, 1, 5);
		RgbLedDriver_TurnOn((i + 8 ) % 16 + 1, 5, 5, 5);
		RgbLedDriver_TurnOn((i + 9 ) % 16 + 1, 5, 1, 1);
		RgbLedDriver_TurnOn((i + 10) % 16 + 1, 1, 5, 1);
		RgbLedDriver_TurnOn((i + 11) % 16 + 1, 1, 1, 5);
		RgbLedDriver_TurnOn((i + 12) % 16 + 1, 5, 5, 5);
		RgbLedDriver_TurnOn((i + 13) % 16 + 1, 5, 1, 1);
		RgbLedDriver_TurnOn((i + 14) % 16 + 1, 1, 5, 1);
		RgbLedDriver_TurnOn((i + 15) % 16 + 1, 1, 1, 5);
		RgbLedDriver_TurnOn((i + 16) % 16 + 1, 5, 5, 5);
		/**/
		RotaryEncoder_Read();
		i = RotaryEncoder_GetRotation();
		RgbLedDriver_TurnOn(1, i + 5, 5, 5);
	}
}
