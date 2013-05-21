#include "version.h"
#include "I2CSlaveDriver.h"
#include "RgbLedDriver.h"

uint8_t command = 0;
uint8_t led = 0;

void I2CSlaveDriver_processCommand(void)
{
	uint8_t red, green, blue;

	command = I2C_Read();

	switch (command) {
		case GET_LED_COLOUR:
			led = I2C_Read();
			break;
		case SET_LED_COLOUR:
			led = I2C_Read();
			red = I2C_Read();
			green = I2C_Read();
			blue = I2C_Read();
			RgbLedDriver_TurnOn(led, red, green, blue);
			break;
		default:
			/* TODO: Runtime error? */
			break;
	}
}

void I2CSlaveDriver_sendData(void)
{
	switch (command) {
		case GET_VERSION:
			I2C_WriteString(RGB_ENCODER_FIRMWARE_VERSION);
			break;
		case GET_LED_COLOUR:
			I2C_Write(RgbLedDriver_GetLedColour(led, RED));
			I2C_Write(RgbLedDriver_GetLedColour(led, GREEN));
			I2C_Write(RgbLedDriver_GetLedColour(led, BLUE));
			break;
		default:
			/* TODO: Runtime error? */
			break;
	}
}
