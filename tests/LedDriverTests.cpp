
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
	CHECK_EQUAL(0x41, virtualLeds);
}

TEST(LedDriver, TurnLedOneOnTwice)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(1);
	CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL(0x41, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(2);
	CHECK_EQUAL(0x01, virtualLeds);
}

TEST(LedDriver, TurnOffAllLeds)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	CHECK_EQUAL(0x00, virtualLeds);
}

TEST(LedDriver, AllOnMasksUnusedBits)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL(0x41, virtualLeds);
	virtualLeds = 0xFF;
	CHECK_EQUAL(0xFF, virtualLeds);
}

TEST(LedDriver, AllOffMasksUnusedBits)
{
	LedDriver_TurnAllOff();
	CHECK_EQUAL(0x00, virtualLeds);
	virtualLeds = 0xff;
	LedDriver_TurnAllOff();
	CHECK_EQUAL(0xBE, virtualLeds);
}
