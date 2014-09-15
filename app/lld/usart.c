#include "usart.h"

// Will set the baudrate register given the peripheral clocl value and the
// Desired baudrate
static uint16_t setBaudrateRegister(uint32_t baudrate, uint32_t clockFreq,
                                    uint8_t isOver8) {
    uint16_t integer = clockFreq / baudrate;

    if (isOver8) {
        integer = 2 * clockFreq / baudrate;
        // Weird thing we have to do if we are only oversampling by 8
        integer = (integer & 0xFFF0) | ((integer & 0x000F) >> 1);
    }

    assert(integer > 0);
    return integer;
}

void usartInit(USART_TypeDef *usart, uint32_t baudrate) {
    assert(usart == USART1 || usart == USART2);

    if (usart == USART1) {
        rccEnableUSART1();
    } else if (usart == USART2) {
        rccEnableUSART2();
    }

    usart->BRR = setBaudrateRegister(baudrate, SystemCoreClock, 0);

    usart->CR2 = 0;
    usart->CR3 = 0;
    usart->CR1 = USART_CR1_UE | USART_CR1_TE;
}

void usartPutChar(USART_TypeDef *usart, uint8_t byte) {
    assert(usart == USART1 || usart == USART2);
    while(!(usart->ISR & USART_ISR_TXE));
    usart->TDR = byte;
}