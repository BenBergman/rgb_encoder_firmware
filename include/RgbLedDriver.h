#ifndef RGBLEDDRIVER_H_PCE9AR5O
#define RGBLEDDRIVER_H_PCE9AR5O

#include <stdint.h>

void RgbLedDriver_Create(void);
void RgbLedDriver_TurnOn(int led, uint8_t r, uint8_t g, uint8_t b);

#endif /* end of include guard: RGBLEDDRIVER_H_PCE9AR5O */
