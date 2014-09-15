#ifndef VARIOUS_H
#define VARIOUS_H

#include "stm32l053xx.h"

static inline void assert(uint8_t condition) {
    if (!condition) {
        __BKPT(0);
        while(1);
    }
}

void delay(uint32_t ms);

#endif