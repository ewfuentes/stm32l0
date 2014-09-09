#include "i2c.h"

#define I2C_READ 0
#define I2C_WRITE 1

static uint32_t setupTiming(i2cSpeed_t spd, uint32_t clockFreq) {
    (void) spd;
    (void) clockFreq;
    uint32_t presc = 0;
    uint32_t sdadel = 2;
    uint32_t scldel = 2;
    uint32_t scll = 9;
    uint32_t sclh = 9;

    return  presc << 28 |
            scldel << 20 |
            sdadel << 16 |
            sclh << 8 |
            scll;
}

void i2cInit(I2C_TypeDef *i2c, i2cSpeed_t spd) {
    assert(i2c == I2C1 || i2c == I2C2);
    assert(spd < i2cSpeed_count);

    if (i2c == I2C1) {
        rccEnableI2C1();
    } else if (i2c == I2C2) {
        rccEnableI2C2();
    }

    // Setup timing register
    i2c->TIMINGR = setupTiming(spd, SystemCoreClock);
    
    // Reset state
    i2c->CR1 &= ~I2C_CR1_PE;
}

static uint32_t i2cSetup(uint32_t addr, uint8_t direction) {
    uint32_t ret = 0;
    if (addr & I2C_10BIT_ADDR) {
        ret = (addr & 0x000003FF) | I2C_CR2_ADD10;
    } else {
        // 7 Bit Address
        ret = (addr & 0x0000007F) << 1;
    }

    if (direction == I2C_READ) {
        ret |= I2C_CR2_RD_WRN;
        if (addr & I2C_10BIT_ADDR) {
            ret |= I2C_CR2_HEAD10R;
        }
    }

    return ret;
}

// Will return the number of data bytes written to the device
uint32_t i2cWrite(I2C_TypeDef *i2c, uint32_t addr, uint8_t *txBuffer, 
                    uint32_t len) {
    assert(i2c == I2C1 || i2c == I2C2);
    assert(txBuffer != NULL);
    assert(len > 0);

    i2c->CR1 &= ~I2C_CR1_PE;
    i2c->CR2 = 0;

    i2c->CR2 = i2cSetup(i2c, addr, I2C_WRITE);

    if (len > 0xFF) {
        i2c->CR2 |= 0x00FF0000 | I2C_CR2_RELOAD; 
    } else {
        i2c->CR2 |= ((len & 0xFF) << 16);
    }
    i2c->CR1 |= I2C_CR1_PE;
    i2c->CR2 |= I2C_CR2_START;
    while(i2c->CR2 & I2C_CR2_START);
    uint32_t numTxBytes = 0;
    while (numTxBytes < len) {
        if (i2c->ISR & I2C_ISR_NACKF) {
            // Was not acknowledged, disable device and exit
            i2c->CR1 &= ~I2C_CR1_PE;
            return numTxBytes;
        }

        if (i2c->ISR & I2C_ISR_TXIS) {
            // Device acknowledged and we must send the next byte
            i2c->TXDR = txBuffer[numTxBytes++];
        } else {
            continue;
        }
    }
    

}

// uint8_t i2cRead(I2C_TypeDef *i2c, uint8_t addr, uint8_t )