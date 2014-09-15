#include "various.h"


static volatile uint32_t delayTime = 0;
volatile uint32_t ticks = 0;

inline void assert(uint8_t condition) {
    if (!condition) {
        __BKPT(0);
        while(1);
    }
}

void SysTick_Handler(void) {
    ticks++;
    if (delayTime > 0){
        delayTime--;    
    }
}

void delay(uint32_t delayMillis) {
    delayTime = delayMillis;

    while(delayTime > 0);
}