
extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

//static uint16_t *ledsAddress;

TEST_GROUP(LedDriver)
{
};

TEST(LedDriver, LedsOffAfterCreate)
{
	uint8_t virtualLeds = 0xff;
	LedDriver_Create(&virtualLeds);
	CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	uint8_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	uint8_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CHECK_EQUAL(0, virtualLeds);
}
