#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
	#include "RotaryEncoder.h"
}

uint8_t encoderAddress = 0x00;

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
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x03;
	RotaryEncoder_Read();
	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	CHECK_EQUAL(-1, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, SinglePositiveRotationDetected)
{
	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x03;
	RotaryEncoder_Read();
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	CHECK_EQUAL(1, RotaryEncoder_GetRotation());
}

TEST(RotaryEncoder, MultiplePositiveRotationsDetected)
{
	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x03;
	RotaryEncoder_Read();
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x03;
	RotaryEncoder_Read();
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	encoderAddress = 0x02;
	RotaryEncoder_Read();
	encoderAddress = 0x03;
	RotaryEncoder_Read();
	encoderAddress = 0x01;
	RotaryEncoder_Read();
	encoderAddress = 0x00;
	RotaryEncoder_Read();

	CHECK_EQUAL(3, RotaryEncoder_GetRotation());
}


/*
 * Test List:
 * ==========
 *	✔ rotary encoder initialization clears rotation
 *	- encoder change is reflected correctly
 *		✔ can detect single notch rotation
 *		- can detect several notch rotation
 *		- forward and backward
 *	- bad rotations (ie jumps) are dealt with correctly
 *	- rotations are cumulative
 *		- forward + forward
 *		- forward + backwards
 *		- backward + forward
 *		- backward + backward
 *	- can clear rotation amount
 */
