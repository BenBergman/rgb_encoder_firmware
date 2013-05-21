#ifndef I2CSLAVEDRIVER_H_OQKF4U8V
#define I2CSLAVEDRIVER_H_OQKF4U8V

#include "I2C.h"

enum I2C_COMMANDS {
	GET_VERSION = 0x00,
	GET_LED_COLOUR = 0x10,
	SET_LED_COLOUR = 0x80
};

void I2CSlaveDriver_processCommand(void);
void I2CSlaveDriver_sendData(void);

#endif /* end of include guard: I2CSLAVEDRIVER_H_OQKF4U8V */
