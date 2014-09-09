#include <stdint.h>
#include <string.h>

#include "lld.h"
#include "gde021a1.h"


#define RED_LED GPIOA, 5
#define GREEN_LED GPIOB, 4

#define COLOR_SCL GPIOB, 6
#define COLOR_SDA GPIOB, 7
#define COLOR_INT GPIOB, 12

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

    gde021a1Init();

    gde021a1Test();
    

    while(1){
        delay(500);
        gpioTogglePin(GREEN_LED);
    }

    return 0;
}