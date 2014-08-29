#include <stdint.h>
#include <string.h>

#include "lld.h"


#define RED_LED GPIOA, 5
#define GREEN_LED GPIOB, 4

#define SPI_SS GPIOB, 12
#define SPI_SCK GPIOB, 13
#define SPI_MISO GPIOB, 14
#define SPI_MOSI GPIOB, 15

static volatile uint32_t delayTime = 0;
volatile uint32_t ticks = 0;

void HardFault_Handler(void) {
    __BKPT(1);
    while(1);
}

void SysTick_Handler(void) {
    ticks++;
    if (delayTime > 0){
        delayTime--;    
    }
    gpioTogglePin(RED_LED);
}

void delay(uint32_t delayMillis) {
    delayTime = delayMillis;

    while(delayTime > 0);
}

int main() {
    if (SysTick_Config(SystemCoreClock/1000)) {
        while(1);
    }
    rccEnableGPIOA();
    rccEnableGPIOB();

    gpioPinMode(GREEN_LED, gpioMode_output);
    gpioPinMode(RED_LED, gpioMode_output);

    gpioPinMode(SPI_MISO, gpioMode_alternate);
    gpioPinMode(SPI_MOSI, gpioMode_alternate);
    gpioPinMode(SPI_SCK, gpioMode_alternate);
    gpioPinMode(SPI_SS, gpioMode_output);

    gpioOutputSpeed(SPI_SCK, gpioSpeed_high);
    gpioOutputSpeed(SPI_MISO, gpioSpeed_high);
    gpioOutputSpeed(SPI_MOSI, gpioSpeed_high);



    gpioSetPin(SPI_SS);

    gpioAlternate(SPI_SCK, 0);
    gpioAlternate(SPI_MISO, 0);
    gpioAlternate(SPI_MOSI, 0);
    
    spiInit(SPI2, 500000);

    uint8_t rxBuffer[4] = {0};
    uint8_t txBuffer[4] = {0xAA,0x55, 0x55, 0xAA};
    while(1){
        delay(500);
        gpioTogglePin(GREEN_LED);
        // memcpy(txBuffer, (const void *) &ticks, 4);
        spiSendReceive(SPI2, 4, txBuffer, rxBuffer, SPI_SS);
    }

    return 0;
}