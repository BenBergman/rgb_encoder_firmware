
extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

static uint8_t virtualLeds;

TEST_GROUP(LedDriver)
{
	void setup()
	{
		LedDriver_Create(&virtualLeds);
	}
};

TEST(LedDriver, LedsOffAfterCreate)
{
	virtualLeds = 0xff;
	LedDriver_Create(&virtualLeds);
	CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(2);
	CHECK_EQUAL(0x21, virtualLeds);
}

TEST(LedDriver, TurnLedOneOnTwice)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(1);
	CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(2);
	LedDriver_TurnOff(2);
	CHECK_EQUAL(0x01, virtualLeds);
}
