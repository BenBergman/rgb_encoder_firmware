#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "I2CSlaveDriver.h"
#include "CppUTestExt/MockSupport_c.h"

	void I2C_Write(uint8_t value)
	{
		mock_c()->actualCall("I2C_Write")
			->withIntParameters("value", value);
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
