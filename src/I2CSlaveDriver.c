#include "I2CSlaveDriver.h"
#include "RgbLedDriver.h"

void I2CSlaveDriver_processCommand(void)
{
	uint8_t command, led, red, green, blue;

	command = I2C_Read();

	switch (command) {
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
	I2C_Write(0);
}
