#ifndef I2C_H_IXML6WWR
#define I2C_H_IXML6WWR

#include <stdint.h>

uint8_t I2C_Read(void);
void I2C_Write(uint8_t data);
void I2C_WriteString(char *data);

#endif /* end of include guard: I2C_H_IXML6WWR */
