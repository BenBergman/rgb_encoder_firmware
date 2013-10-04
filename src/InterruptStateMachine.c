#include "InterruptStateMachine.h"

void InterruptStateMachine_Create(uint8_t* interruptAddress, uint8_t interruptBit)
{
	(void) interruptBit;

	*interruptAddress = 1;
}

void InterruptStateMachine_ReadInputs(void)
{
}
