#include "nxpsl3s.h"

#define RFID_ADDR 0x51

#define RFID_SCL GPIOB, 6
#define RFID_SDA GPIOB, 7
#define RFID_INT GPIOB, 12

I2C_TypeDef *rfidi2c = I2C1;

#define RFID_TAG rfidi2c, RFID_ADDR | I2C_7BIT_ADDR

uint32_t readRegister(uint16_t reg, uint8_t *buf, uint32_t numBytes) {
    uint8_t regBuf[] = {(reg & 0xFF00) >> 8, reg & 0xFF};
    while (i2cWrite(RFID_TAG, regBuf, 2) != 2);
        
    while (i2cRead(RFID_TAG, buf, numBytes) != numBytes);
    return 2;
}

uint32_t writeShort(uint16_t reg, uint16_t data) {
    assert((reg & 0x0001) == 0);
    uint8_t buf[] = {(reg & 0xFF00) >> 8, reg & 0xFF, 
        (data & 0xFF00) >> 8, data & 0xFF};
    while(i2cWrite(RFID_TAG, buf, 4) != 4);
    return 2;
}

uint16_t rfidReadConfig() {
    uint8_t buf[2] = {0};
    readRegister(0x2040, buf, 2);
    return buf[0] << 8 | buf[1];
}

uint16_t rfidReadDownloadReg() {
    uint8_t buf[2] = {0};
    readRegister(0x203E, buf, 2);
    return buf[0] << 8 | buf[1];
}

uint16_t rfidWriteDownloadReg(uint16_t data) {
    return writeShort(0x203E, data);
}

void rfidInit() {
    gpioOutputType(RFID_SCL, gpioOutputType_openDrain);
    gpioOutputType(RFID_SDA, gpioOutputType_openDrain);
    gpioPinMode(RFID_SCL, gpioMode_alternate);
    gpioPinMode(RFID_SDA, gpioMode_alternate);
    gpioAlternate(RFID_SCL, 1);
    gpioAlternate(RFID_SDA, 1);


    uint8_t buff[32] = {0};
    i2cInit(rfidi2c, i2cSpeed_std);
    
    readRegister(0x2040, buff, 2);

    readRegister(0x2004, buff, 0x14);
    
    if ((buff[6] == 0x00 &&
        buff[7] == 0x00 &&
        buff[8] == 0x00 &&
        buff[9] == 0x00) ||
        buff[10] != 0x00 ||
        buff[11] != 0x00 ||
        buff[12] != 0x00 ||
        buff[13] != 0x00) {
        writeShort(0x2008, 0xCAFE);
        delay(10);
        writeShort(0x200A, 0xD00D);
        delay(10);

        uint16_t i = 0x200C;
        for (; i < 0x2018; i+=2) {
            writeShort(i, 0x0000);
            delay(10);
        }
    }
}
