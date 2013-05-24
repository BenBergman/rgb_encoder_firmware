#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
	#include "RotaryEncoder.h"
}

uint8_t encoderAddress = 0x00;

uint8_t positiveStates[] = {0x02, 0x03, 0x01, 0x00};
uint8_t negativeStates[] = {0x01, 0x03, 0x02, 0x00};

static void RotateFullPositiveNotches(int rotations)
{
	for (int i = 0; i < rotations * 4; i++) {
		encoderAddress = positiveStates[i%4];
		RotaryEncoder_Read();
	}
}

static void RotateFullNegativeNotches(int rotations)
{
	for (int i = 0; i < rotations * 4; i++) {
		encoderAddress = negativeStates[i%4];
		RotaryEncoder_Read();
	}
}

TEST_GROUP(RotaryEncoder)
{
	void setup() {
		encoderAddress = 0x00;
		RotaryEncoder_Create(&encoderAddress);
	}
};

TEST(RotaryEncoder, CreateClearsRotation)
{
	CHECK_EQUAL(0, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, SingleNegativeRotationDetected)
{
	RotateFullNegativeNotches(1);

	CHECK_EQUAL(-1, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, SinglePositiveRotationDetected)
{
	RotateFullPositiveNotches(1);

	CHECK_EQUAL(1, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, MultiplePositiveRotationsDetected)
{
	RotateFullPositiveNotches(3);

	CHECK_EQUAL(3, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, MultipleNegativeRotationsDetected)
{
	RotateFullNegativeNotches(4);

	CHECK_EQUAL(-4, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, CombinationForwardAndBackRotationsCancel)
{
	RotateFullPositiveNotches(10);
	RotateFullNegativeNotches(5);

	CHECK_EQUAL(5, RotaryEncoder_GetRotation());

	RotateFullPositiveNotches(1);
	RotateFullNegativeNotches(8);

	CHECK_EQUAL(-2, RotaryEncoder_GetRotation());

	RotateFullNegativeNotches(4);
	RotateFullPositiveNotches(10);

	CHECK_EQUAL(4, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, CanClearRotations)
{
	RotateFullPositiveNotches(3);
	RotaryEncoder_ResetRotation();

	CHECK_EQUAL(0, RotaryEncoder_GetRotation());

	RotateFullNegativeNotches(7);
	RotaryEncoder_ResetRotation();

	CHECK_EQUAL(0, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, CanHandleBadRotations)
{
	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	CHECK_EQUAL(1, RotaryEncoder_GetRotation());
}


/*
 * Test List:
 * ==========
 *	✔ rotary encoder initialization clears rotation
 *	✔ encoder change is reflected correctly
 *		✔ can detect single notch rotation
 *		✔ can detect several notch rotation
 *		✔ forward and backward
 *	- bad rotations (ie jumps) are dealt with correctly
 *	✔ rotations are cumulative
 *		- forward + forward
 *		- forward + backwards
 *		- backward + forward
 *		- backward + backward
 *	✔ can clear rotation amount
 */
