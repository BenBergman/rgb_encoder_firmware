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
		case 0x10:
			led = I2C_Read();
			break;
		case 0x80:
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
		case 0x00:
			I2C_WriteString(RGB_ENCODER_FIRMWARE_VERSION);
			break;
		case 0x10:
			I2C_Write(0x50);
			I2C_Write(0x60);
			I2C_Write(0x70);
			break;
		default:
			/* TODO: Runtime error? */
			break;
	}
}
