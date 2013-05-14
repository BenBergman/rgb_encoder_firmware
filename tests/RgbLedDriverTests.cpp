extern "C"
{
#include "RgbLedDriver.h"
#include "ws2811_hs.h"
	uint8_t ws2811SpyLeds[16 * 3] = {0xff};
	uint16_t ws2811SpyLength = 0;
	uint8_t ws2811SpyPinMask = 0;
	int ws2811SpyCallCount = 0;

	void ws2811Spy_Reset(void)
	{
		for (int i = 0; i < 16 * 3; i++)
			ws2811SpyLeds[i] = 0xff;
		ws2811SpyLength = 0;
		ws2811SpyPinMask = 0;
		ws2811SpyCallCount = 0;
	}

	void write_ws2811_hs(uint8_t *data, uint16_t length, uint8_t pinmask)
	{
		ws2811SpyLength = length;
		ws2811SpyPinMask = pinmask;
		for (int i = 0; i < length; i++)
			ws2811SpyLeds[i] = data[i];
	}

	uint8_t *ws2811Spy_GetLeds(void)
	{
		return ws2811SpyLeds;
	}

	uint16_t ws2811Spy_GetLength(void)
	{
		return ws2811SpyLength;
	}

	uint8_t ws2811Spy_GetPinMask(void)
	{
		return ws2811SpyPinMask;
	}

	int ws2811Spy_GetCallCount(void)
	{
		return ws2811SpyCallCount;
	}
}

#include "CppUTest/TestHarness.h"


TEST_GROUP(RgbLedDriver)
{
	void setup()
	{
		ws2811Spy_Reset();
	}
};

TEST(RgbLedDriver, LedsOffAfterCreate)
{
	RgbLedDriver_Create();

	for (int i = 0; i < 16 * 3; i++)
		CHECK_EQUAL(0, ws2811Spy_GetLeds()[i]);
}

TEST(RgbLedDriver, TurnOnLedOne)
{
	RgbLedDriver_TurnOn(1, 0x10, 0x20, 0x30);

	CHECK_EQUAL(0x20, ws2811Spy_GetLeds()[0])
	CHECK_EQUAL(0x10, ws2811Spy_GetLeds()[1])
	CHECK_EQUAL(0x30, ws2811Spy_GetLeds()[2])
	for (int i = 1 * 3; i < 16 * 3; i++)
		CHECK_EQUAL(0, ws2811Spy_GetLeds()[i]);
}

/*
 * TODO Test List
 *	✔ create turns off all leds?
 *	- turn on/off single LED
 *	- turn on/off multiple LEDs
 *	- get colour of single LED
 *	- get colour of all LEDs
 */
