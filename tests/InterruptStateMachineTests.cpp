#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
	#include "InterruptStateMachine.h"
	#include "RotaryEncoder.h"
}

static uint8_t encoderAddress = 0x03;

static uint8_t positiveStates[] = {0x02, 0x00, 0x01, 0x03};
/*
static uint8_t negativeStates[] = {0x01, 0x00, 0x02, 0x03};
*/

static void RotateFullPositiveNotches(int rotations)
{
	for (int i = 0; i < rotations * 4; i++) {
		encoderAddress = positiveStates[i%4];
		RotaryEncoder_Read();
	}
}

/*
static void RotateFullNegativeNotches(int rotations)
{
	for (int i = 0; i < rotations * 4; i++) {
		encoderAddress = negativeStates[i%4];
		RotaryEncoder_Read();
	}
}
*/

TEST_GROUP(InterruptStateMachine)
{
	void setup()
	{
		encoderAddress = 0x03;
		RotaryEncoder_Create(&encoderAddress, 0, 1);
	}

	void teardown()
	{
	}
};

TEST(InterruptStateMachine, NewRotationTriggersIntLine)
{
	uint8_t interruptAddress = 0;
	InterruptStateMachine_Create(&interruptAddress, 1);
	RotateFullPositiveNotches(1);
	InterruptStateMachine_ReadInputs();

	CHECK_EQUAL(1, interruptAddress);
}

/*
 * Test List:
 * ==========
 *	✔ new rotation data triggers interrupt line
 *  - touch triggers interrupt line
 *  - click triggers interrupt line
 *  - rotation then read rotation clears interrupt line
 *  - touch then read touch clears interrupt line
 *  - click then read click clears interrupt line
 *  - rotation and touch, then read touch does not clear interrupt line
 *  - rotation and touch, then read rotation and touch clears interrupt line
 */
