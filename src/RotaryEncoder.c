#include "RotaryEncoder.h"

static int8_t enc_states[] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};

static int rotation;
static int directionCounter;
static uint8_t *encoderAddress;
static uint8_t encA, encB;
static uint8_t encoderHistory = 0;

void RotaryEncoder_Create(uint8_t *encoder, uint8_t encABit, uint8_t encBBit)
{
	encoderAddress = encoder;
	encoderHistory = 0x03;
	RotaryEncoder_ResetRotation();
	encA = encABit;
	encB = encBBit;
}

int RotaryEncoder_GetRotation()
{
	return rotation;
}

static uint8_t GetBitMaskFromBit(uint8_t bit)
{
	return (uint8_t)(1 << bit);
}

static uint8_t RotaryEncoder_ReadEncoderRegister(void)
{
	uint8_t encAVal = *encoderAddress & GetBitMaskFromBit(encA);
	uint8_t encBVal = *encoderAddress & GetBitMaskFromBit(encB);

	return (uint8_t)((encAVal >> encA) | (encBVal >> (encB - 1)));
}

static void RotaryEncoder_AddStateToHistory(uint8_t encoderState)
{
	encoderHistory = (uint8_t) (encoderHistory << 2);
	encoderHistory = (uint8_t) (encoderHistory | encoderState);
}

static void RotaryEncoder_AddRotations(void)
{
	int direction = (directionCounter < 0) ? -1 : 1;
	while (directionCounter * direction > 0) {
		directionCounter -= 4 * direction;
		rotation += direction;
		if (directionCounter * direction < 0)
			directionCounter = 0;
	}
}

void RotaryEncoder_Read()
{
	uint8_t encoderState = RotaryEncoder_ReadEncoderRegister();
	RotaryEncoder_AddStateToHistory(encoderState);
	directionCounter += enc_states[encoderHistory & 0x0F];

	if (encoderState == 0x03) {
		RotaryEncoder_AddRotations();
	}
}

void RotaryEncoder_ResetRotation()
{
	rotation = 0;
}

/*
 * CW
 *  A | B
 * ---+---
 *  1 | 1
 *  1 | 0
 *  0 | 0
 *  0 | 1
 *  1 | 1
 *
 * CCW
 *  A | B
 * ---+---
 *  1 | 1
 *  0 | 1
 *  0 | 0
 *  1 | 0
 *  1 | 1
 */
