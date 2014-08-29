#ifndef SPI_H
#define SPI_H

#include "lld.h"

void spiInit(SPI_TypeDef *spi, uint32_t baudRate);

uint32_t spiSendReceive(SPI_TypeDef *spi, uint32_t numBytes, 
                        uint8_t *txBuf, uint8_t *rxBuf, 
                        GPIO_TypeDef *slavePort, uint8_t slavePinNum);

#endif