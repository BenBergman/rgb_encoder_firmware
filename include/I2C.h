#ifndef I2C_H_IXML6WWR
#define I2C_H_IXML6WWR

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void I2C_Init(uint8_t addr, void (*function)(int));
EXTERNC bool I2C_DataAvailable(void);
EXTERNC uint8_t I2C_Read(void);
EXTERNC void I2C_Write(uint8_t data);
EXTERNC void I2C_WriteString(char *data);

#undef EXTERNC

#endif /* end of include guard: I2C_H_IXML6WWR */
