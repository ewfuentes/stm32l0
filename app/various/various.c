#include "various.h"

static volatile uint32_t delayTime = 0;
volatile uint32_t ticks = 0;

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

void HardFault_Handler(void) {
    __BKPT(1);
    while(1);
}