#ifndef VARIOUS_H
#define VARIOUS_H

#include "stm32l053xx.h"

inline void assert(uint8_t condition);
void delay(uint32_t delayMillis);
void SysTick_Handler(void);


#endif