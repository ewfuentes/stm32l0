#ifndef USART_H
#define USART_H

#include "lld.h"

void usartInit(USART_TypeDef *usart, uint32_t baudrate);
void usartPutChar(USART_TypeDef *usart, uint8_t byte);
#endif