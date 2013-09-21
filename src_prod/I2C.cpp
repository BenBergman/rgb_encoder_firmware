#include <I2C.h>
#include <msp430.h>
#include <Wire.h>

void I2C_Init(uint8_t addr, void (*function)(int))
{
	Wire.begin(addr);
	Wire.onReceive(function);
}

void I2C_Write(uint8_t data)
{
	(void)data;
}

void I2C_WriteString(char *data)
{
	(void)data;
}

bool I2C_DataAvailable(void)
{
	Wire.available();
}

uint8_t I2C_Read()
{
	return Wire.read();
}
