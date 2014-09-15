#include "tcs34725.h"

#define COLOR_SCL GPIOB, 6
#define COLOR_SDA GPIOB, 7
#define COLOR_INT GPIOB, 12

#define COLOR_ADDR 0x29
#define COLOR_COMMAND 0x00
#define COLOR_COMMAND_CMD 0x80
#define COLOR_COMMAND_AUTOINC 0x20

#define COLOR_ENABLE 0x00
#define COLOR_ENABLE_AIEN 0x10
#define COLOR_ENABLE_AEN 0x02
#define COLOR_ENABLE_PON 0x01

#define COLOR_ATIME 0x01
#define COLOR_ATIME_DEFAULT 0xFC

#define COLOR_CTRL 0x0F
#define COLOR_CTRL_AGAIN_X1 0x00
#define COLOR_CTRL_AGAIN_X4 0x01
#define COLOR_CTRL_AGAIN_X16 0x02
#define COLOR_CTRL_AGAIN_X64 0x03

#define COLOR_ID 0x12
#define COLOR_ID_TCS34725 0x44

#define COLOR_STATUS 0x13
#define COLOR_STATUS_VALID 0x01
#define COLOR_CLEAR_LOW 0x14

#define COLOR_RED_THRESHOLD 0x400
#define COLOR_GREEN_THRESHOLD 0x380
#define COLOR_BLUE_THRESHOLD 0x800

I2C_TypeDef *colori2c = I2C1;

void colorInit() {
    gpioOutputType(COLOR_SCL, gpioOutputType_openDrain);
    gpioOutputType(COLOR_SDA, gpioOutputType_openDrain);
    gpioPinMode(COLOR_SCL, gpioMode_alternate);
    gpioPinMode(COLOR_SDA, gpioMode_alternate);
    gpioAlternate(COLOR_SCL, 1);
    gpioAlternate(COLOR_SDA, 1);

    i2cInit(colori2c, i2cSpeed_std);

    uint8_t data[10] = {0};
    data[0] = COLOR_COMMAND_CMD | COLOR_ATIME;
    data[1] = COLOR_ATIME_DEFAULT;
    i2cWrite(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 2);

    data[0] = COLOR_COMMAND_CMD | COLOR_CTRL;
    data[1] = COLOR_CTRL_AGAIN_X4;
    i2cWrite(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 2);

    data[0] = COLOR_COMMAND_CMD | COLOR_ENABLE;
    data[1] = COLOR_ENABLE_PON;
    i2cWrite(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 2);
    delay(10);

    data[0] = COLOR_COMMAND_CMD | COLOR_ENABLE;
    data[1] = COLOR_ENABLE_PON | COLOR_ENABLE_AEN;
    i2cWrite(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 2);
    delay(10);
}

uint8_t colorRead(uint32_t *red, uint32_t *green, uint32_t *blue,
                  uint32_t *lux) {
    uint8_t status = 0;
    uint8_t data[10] = {0};
    
    data[0] = COLOR_COMMAND_CMD | COLOR_COMMAND_AUTOINC | COLOR_STATUS;
    i2cWrite(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 1);
    i2cRead(colori2c, COLOR_ADDR | I2C_7BIT_ADDR, data, 9);
    status = data[0];
    
    if (status & COLOR_STATUS_VALID){
        *lux = data[1] | (data[2] << 8);
        *red = data[3] | (data[4] << 8);
        *green = data[5] | (data[6] << 8);
        *blue = data[7] | (data[8] << 8);
    }

    return (status & COLOR_STATUS_VALID) ? 0 : 1;

}