#ifndef I2C_H
#define I2C_H

#include "lld.h"

typedef enum {
    i2cSpeed_std,
    i2cSpeed_fast,
    i2cSpeed_fastPlus,
    i2cSpeed_count,
} i2cSpeed_t;

void i2cInit(I2C_TypeDef *i2c, i2cSpeed_t spd);

#define I2C_7BIT_ADDR (0 << 31)
#define I2C_10BIT_ADDR (1 << 31)

// Returns number of bytes written
uint32_t i2cWrite(I2C_TypeDef *i2c, uint32_t addr, uint8_t *txBuffer,
                    uint32_t len);

// Returns number of bytes read
uint32_t i2cRead(I2C_TypeDef *i2c, uint8_t addr, uint8_t *rxBuffer,
                 uint32_t numBytes);

#endif
