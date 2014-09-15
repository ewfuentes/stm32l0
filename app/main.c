#include <stdint.h>
#include <string.h>

#include "lld.h"
#include "gde021a1.h"
#include "printf.h"
#include "tcs34725.h"

#define RED_LED GPIOA, 5
#define GREEN_LED GPIOB, 4

#define COLOR_SCL GPIOB, 6
#define COLOR_SDA GPIOB, 7
#define COLOR_INT GPIOB, 12

#define USART_TX GPIOA, 9
#define USART_RX GPIOA, 10



void HardFault_Handler(void) {
    __BKPT(1);
    while(1);
}

void printfPutC(void *p, char c) {
    usartPutChar((USART_TypeDef *)p, (uint8_t)c);
}

int main() {
    if (SysTick_Config(SystemCoreClock/1000)) {
        while(1);
    }
    rccEnableGPIOA();
    rccEnableGPIOB();

    gpioPinMode(GREEN_LED, gpioMode_output);
    gpioPinMode(RED_LED, gpioMode_output);

    gpioPinMode(USART_RX, gpioMode_alternate);
    gpioPinMode(USART_TX, gpioMode_alternate);
    gpioAlternate(USART_RX, 4);
    gpioAlternate(USART_TX, 4);


    usartInit(USART1, 115200);
    init_printf((void *)USART1, printfPutC);

    gde021a1Init();

    gde021a1Test();

    colorInit();
    
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t lux;

    while(1){
        delay(20);
        // Start reading from the status register
        gpioSetPin(GREEN_LED);
        colorRead(&red, &green, &blue, &lux);
        gpioResetPin(GREEN_LED);
        gpioSetPin(GREEN_LED);
        printf("%d,%d,%d,%d\r\n", red, green, blue, lux);
        gpioResetPin(GREEN_LED);
    }

    return 0;
}