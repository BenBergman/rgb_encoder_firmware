#include "I2CSlaveDriver.h"

void I2CSlaveDriver_processCommand(void)
{
	I2C_Read();
}

void I2CSlaveDriver_sendData(void)
{
	I2C_Write(0);
}
