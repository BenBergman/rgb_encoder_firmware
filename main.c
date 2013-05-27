//#include <msp430g2553.h>   /* Genericizable */
#include <msp430.h>
#include "RgbLedDriver.h"

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

    P1DIR = 0x03;
	P2DIR &= ~(0b11000000);
	P2REN |= 0b11000000;

	RgbLedDriver_Create();

    /* infinite loop */
    for( ; ; ) {
		RgbLedDriver_TurnOn(1 , 5, 1, 1);
		RgbLedDriver_TurnOn(2 , 1, 5, 1);
		RgbLedDriver_TurnOn(3 , 1, 1, 5);
		RgbLedDriver_TurnOn(4 , 5, 5, 5);
		RgbLedDriver_TurnOn(5 , 5, 1, 1);
		RgbLedDriver_TurnOn(6 , 1, 5, 1);
		RgbLedDriver_TurnOn(7 , 1, 1, 5);
		RgbLedDriver_TurnOn(8 , 5, 5, 5);
		RgbLedDriver_TurnOn(9 , 5, 1, 1);
		RgbLedDriver_TurnOn(10, 1, 5, 1);
		RgbLedDriver_TurnOn(11, 1, 1, 5);
		RgbLedDriver_TurnOn(12, 5, 5, 5);
		RgbLedDriver_TurnOn(13, 5, 1, 1);
		RgbLedDriver_TurnOn(14, 1, 5, 1);
		RgbLedDriver_TurnOn(15, 1, 1, 5);
		RgbLedDriver_TurnOn(16, 5, 5, 5);
    }
}
