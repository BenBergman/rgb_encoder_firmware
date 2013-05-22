#ifndef ROTARYENCODER_H_QSDKWSJ2
#define ROTARYENCODER_H_QSDKWSJ2

#include <stdint.h>

void RotaryEncoder_Create(uint8_t *encoder);
int RotaryEncoder_GetRotation(void);
void RotaryEncoder_Read(void);

#endif /* end of include guard: ROTARYENCODER_H_QSDKWSJ2 */

