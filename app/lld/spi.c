#include <stdlib.h>
#include "spi.h"

typedef enum {
    spiClockDivider_2,
    spiClockDivider_4,
    spiClockDivider_8,
    spiClockDivider_16,
    spiClockDivider_32,
    spiClockDivider_64,
    spiClockDivider_128,
    spiClockDivider_256,
    spiClockDivider_count
} spiClockDivider_t;

static spiClockDivider_t spiFindClosestDivider(uint32_t baudRate, 
                                               uint32_t clockFreq);

// Will enable the SPI peripheral that was passed to this function
// and it will 
void spiInit(SPI_TypeDef *spi, uint32_t baudRate) {
    assert((spi == SPI1) || spi == SPI2);
    extern uint32_t SystemCoreClock;
    
    if (spi == SPI1) {
        rccEnableSPI1();
    } else if (spi == SPI2) {
        rccEnableSPI2();
    }

    spiClockDivider_t d = spiFindClosestDivider(baudRate, SystemCoreClock);

    // Reset control register and set the baudrate
    spi->CR1 = 0;
    // Set Master Mode and Software control of slave select
    spi->CR1 |= d << 3 | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
}

uint32_t spiSendReceive(SPI_TypeDef *spi, uint32_t numBytes, 
                        uint8_t *txBuf, uint8_t *rxBuf, 
                        GPIO_TypeDef *slavePort, uint8_t slavePinNum) {
    assert((spi == SPI1) || spi == SPI2);
    assert(numBytes > 0);
    assert(slavePort == GPIOA || slavePort == GPIOB || slavePort == GPIOC ||
           slavePort == GPIOD || slavePort == GPIOH);
    assert(slavePinNum < 16);

    uint8_t ignoreRx = 0;
    uint8_t ignoreTx = 0;

    if (rxBuf == NULL) {
        ignoreRx = 1;
    }

    if (txBuf == NULL) {
        ignoreTx = 1;
    }

    gpioResetPin(slavePort, slavePinNum);
    
    spi->CR1 |= SPI_CR1_SPE;
    
    uint32_t numTxBytes = 0;
    uint32_t numRxBytes = 0;
    uint8_t temp = 0;
    while(numTxBytes < numBytes && numRxBytes < numBytes) {

        if ((spi->SR & SPI_SR_TXE) && !ignoreTx && (numTxBytes < numBytes)) {
            spi->DR = txBuf[numTxBytes++];
        } else if ((spi->SR & SPI_SR_TXE) && (numTxBytes < numBytes)) {
            spi->DR = 0; // Send a zero if there is no tx buf
            numTxBytes++;
        }

        if ((spi->SR & SPI_SR_RXNE) && !ignoreRx && (numRxBytes < numBytes)) {
            rxBuf[numRxBytes++] = spi->DR;
        } else if ((spi->SR & SPI_SR_RXNE) && (numRxBytes < numBytes)) {
            numRxBytes++;
            temp = spi->DR; //Read to clear the RXNE flag
            (void)temp;
        }
    }

    while(!(spi->SR & SPI_SR_TXE));
    while(spi->SR & SPI_SR_BSY);
    gpioSetPin(slavePort, slavePinNum);
    spi->CR1 &= ~SPI_CR1_SPE;

    
    return 0;
}

static spiClockDivider_t spiFindClosestDivider(uint32_t baudRate, 
                                               uint32_t clockFreq){
    spiClockDivider_t closest = spiClockDivider_2;
    uint32_t smallestDelta = 0xFFFFFFFF;

    uint8_t i;
    int32_t temp;
    for (i = 0; i < spiClockDivider_count; i++) {
        // The divider we are testing is equal to a right shift by
        // i + 1.  For example, the value of spiClockDivider_32 is 4
        // so in order to get the correct divider, we should right
        // shift by 4 + 1 = 5 which is equal to division by 32.
        temp = clockFreq >> (i + 1);
        temp -= baudRate;
        temp = abs(temp);
        if ((uint32_t)temp < smallestDelta) {
            smallestDelta = temp;
            closest = (spiClockDivider_t) i;
        }
    }

    return closest;
}