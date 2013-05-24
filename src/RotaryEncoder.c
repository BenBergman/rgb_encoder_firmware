#include "RotaryEncoder.h"

static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

static int rotation;
static int directionCounter;
static uint8_t *encoderAddress;
static uint8_t encoderHistory = 0;

void RotaryEncoder_Create(uint8_t *encoder)
{
	encoderAddress = encoder;
	encoderHistory = 0;
	RotaryEncoder_ResetRotation();
}

int RotaryEncoder_GetRotation()
{
	return rotation;
}

void RotaryEncoder_Read()
{
	uint8_t encoderState = (*encoderAddress & 0x03);
	encoderHistory = (uint8_t) (encoderHistory << 2);
	encoderHistory = (uint8_t) (encoderHistory | encoderState);
	directionCounter += enc_states[encoderHistory & 0x0F];

	if (encoderState == 0x00) {
		while (directionCounter > 0) {
			directionCounter -= 4;
			rotation++;
			if (directionCounter < 0)
				directionCounter = 0;
		}
		while (directionCounter < 0) {
			directionCounter += 4;
			rotation--;
			if (directionCounter > 0)
				directionCounter = 0;
		}
	}
}

void RotaryEncoder_ResetRotation()
{
	rotation = 0;
}
