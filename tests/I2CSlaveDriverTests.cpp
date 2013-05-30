#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "version.h"
#include "I2CSlaveDriver.h"
#include "RgbLedDriver.h"
#include "RotaryEncoder.h"
#include "CppUTestExt/MockSupport_c.h"

	void I2C_Write(uint8_t data)
	{
		mock_c()->actualCall("I2C_Write")
			->withIntParameters("data", data);
	}

	void I2C_WriteString(char *data)
	{
		mock_c()->actualCall("I2C_WriteString")
			->withStringParameters("data", data);
	}

	uint8_t I2C_Read()
	{
		mock_c()->actualCall("I2C_Read");

		return (uint8_t)mock_c()->returnValue().value.intValue;
	}
}

static uint8_t encoderAddress;

TEST_GROUP(I2CSlaveDriver)
{
	void setup()
	{
		encoderAddress = 0x03;
		RotaryEncoder_Create(&encoderAddress, 0, 1);
	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
	}
};

TEST(I2CSlaveDriver, ProcessCommandReadsInCommandByte)
{
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0xFF);

	I2CSlaveDriver_processCommand();
}

TEST(I2CSlaveDriver, GetVersionCommandReturnsVersion)
{
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x00);

	I2CSlaveDriver_processCommand();

	mock().expectOneCall("I2C_WriteString")
		.withParameter("data", RGB_ENCODER_FIRMWARE_VERSION);

	I2CSlaveDriver_sendData();
}

TEST(I2CSlaveDriver, SetSingleLedCommandSetsSingleLed)
{
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x80);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x01);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x10);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x20);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x30);

	I2CSlaveDriver_processCommand();

	CHECK_EQUAL(0x10, RgbLedDriver_GetLedColour(1, RED));
	CHECK_EQUAL(0x20, RgbLedDriver_GetLedColour(1, GREEN));
	CHECK_EQUAL(0x30, RgbLedDriver_GetLedColour(1, BLUE));
}

TEST(I2CSlaveDriver, GetSingleLedColour)
{
	RgbLedDriver_TurnOn(1, 0x50, 0x60, 0x70);

	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x10);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)1);

	I2CSlaveDriver_processCommand();

	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x50);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x60);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x70);

	I2CSlaveDriver_sendData();
}

TEST(I2CSlaveDriver, GetMultipleLedColours)
{
	RgbLedDriver_TurnOn(7, 0x50, 0x60, 0x70);
	RgbLedDriver_TurnOn(8, 0x05, 0x06, 0x07);

	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x10);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)7);

	I2CSlaveDriver_processCommand();

	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x50);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x60);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x70);

	I2CSlaveDriver_sendData();

	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x10);
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)8);

	I2CSlaveDriver_processCommand();

	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x05);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x06);
	mock().expectOneCall("I2C_Write")
		.withParameter("data", 0x07);

	I2CSlaveDriver_sendData();
}

static uint8_t positiveStates[] = {0x02, 0x00, 0x01, 0x03};

static void RotateFullPositiveNotches(int rotations)
{
	for (int i = 0; i < rotations * 4; i++) {
		encoderAddress = positiveStates[i%4];
		RotaryEncoder_Read();
	}
}

static void I2CGetRotation(int expectedValue)
{
	mock().expectOneCall("I2C_Read")
		.andReturnValue((uint8_t)0x20);

	I2CSlaveDriver_processCommand();

	mock().expectOneCall("I2C_Write")
		.withParameter("data", expectedValue);

	I2CSlaveDriver_sendData();
}

TEST(I2CSlaveDriver, GetSingleRotation)
{
	RotateFullPositiveNotches(1);
	I2CGetRotation(1);
}

TEST(I2CSlaveDriver, GetMultipleRotations)
{
	RotateFullPositiveNotches(3);
	I2CGetRotation(3);
}

TEST(I2CSlaveDriver, ReadingRotationsResetsRotationCounter)
{
	RotateFullPositiveNotches(3);
	I2CGetRotation(3);
	I2CGetRotation(0);
}

/*
 * Test List:
 * ==========
 * Dispatch actions for each command
 *	✔ get version
 *	- get button/touch status
 *	- get rotation
 *	✔ get single LED colour
 *	✔ get multiple LED colours
 *	- get all LED colours
 *	✔ set single LED colour
 *	- set all LED colours
 *	- toggle interrupt line
 *	- toggle touch notification line
 */
