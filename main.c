//#include <msp430g2553.h>   /* Genericizable */
#include <msp430.h>

#define pin6mask  (0x01 << 6)

int main(void) {
    /* Hold the watchdog timer so it doesn't reset our chip */
    WDTCTL = WDTPW + WDTHOLD;

    /* Configure all pins on port 1 as output pins */
    P1DIR = 0xff;

    /* Set pin 6 high.  Basically, this command sets any combination
     * of the pins on port 1 high.  Pin 0 is 2^0, pin 1 is 2^2, etc.
     * Values can be binary or'd together. Other pins are low.
     */
    P1OUT = pin6mask;

    /* infinite loop */
    for( ; ; ) {
        /* The following two lines implement a very crude delay loop.
         * The actual length of the delay can vary significantly.
         * This approach may not work with all compilers.
         */
        volatile int i;
        for( i = 0; i < 30000; i++ );

        /* Toggle the state of pin 6 on port 1 by exclusive or'ing with
           the mask that represents that pin. */
        P1OUT = P1OUT ^ pin6mask;
    }
}
