#ifndef INTERRUPT_STATE_MACHINE_H
#define INTERRUPT_STATE_MACHINE_H

#include <stdint.h>

void InterruptStateMachine_Create(uint8_t* interruptAddress, uint8_t interruptBit);
void InterruptStateMachine_ReadInputs(void);

#endif
