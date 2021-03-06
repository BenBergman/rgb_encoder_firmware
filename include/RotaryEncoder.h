#ifndef ROTARYENCODER_H_QSDKWSJ2
#define ROTARYENCODER_H_QSDKWSJ2

#include <stdint.h>

void RotaryEncoder_Create(uint8_t *encoder, uint8_t encABit, uint8_t encBBit);
int RotaryEncoder_GetRotation(void);
void RotaryEncoder_Read(void);
void RotaryEncoder_ResetRotation(void);

#endif /* end of include guard: ROTARYENCODER_H_QSDKWSJ2 */

