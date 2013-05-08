#ifndef LEDDRIVER_H_ENGTV4IK
#define LEDDRIVER_H_ENGTV4IK

#include <stdint.h>

void LedDriver_Create(uint8_t *leds);
void LedDriver_TurnOn(int led);
void LedDriver_TurnOff(int led);
void LedDriver_TurnAllOn(void);

#endif /* end of include guard: LEDDRIVER_H_ENGTV4IK */
