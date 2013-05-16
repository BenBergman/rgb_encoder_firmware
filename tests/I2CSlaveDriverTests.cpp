#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "I2CSlaveDriver.h"
#include "RgbLedDriver.h"
#include "CppUTestExt/MockSupport_c.h"

	void I2C_Write(uint8_t data)
	{
		mock_c()->actualCall("I2C_Write")
			->withIntParameters("data", data);
	}

	uint8_t I2C_Read()
	{
		mock_c()->actualCall("I2C_Read");

		return (uint8_t)mock_c()->returnValue().value.intValue;
	}
}

TEST_GROUP(I2CSlaveDriver)
{
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

	mock().expectOneCall("I2C_Write")
			.withParameter("data", 0);

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

/*
 * Test List:
 * ==========
 * Dispatch actions for each command
 *	- get version
 *	- get button/touch status
 *	- get rotation
 *	- get single LED colour
 *	- get all LED colours
 *	✔ set single LED colour
 *	- set all LED colours
 */
