#include "RotaryEncoder.h"

static int rotation;

void RotaryEncoder_Create(uint8_t *encoder)
{
	(void)encoder;
	rotation = 0;
}

int RotaryEncoder_GetRotation()
{
	return rotation;
}

void RotaryEncoder_Read()
{
	rotation = 1;
}
