#include "RotaryEncoder.h"

static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

static int rotation;
static uint8_t *encoderAddress;
static uint8_t encoderHistory = 0;

void RotaryEncoder_Create(uint8_t *encoder)
{
	encoderAddress = encoder;
	encoderHistory = 0;
	rotation = 0;
}

int RotaryEncoder_GetRotation()
{
	return rotation/4;
}

void RotaryEncoder_Read()
{
	encoderHistory = (uint8_t) (encoderHistory << 2);
	encoderHistory = (uint8_t) (encoderHistory | (*encoderAddress & 0x03));
	rotation += enc_states[encoderHistory & 0x0F];
}

void RotaryEncoder_ResetRotation()
{
	rotation = 0;
}
