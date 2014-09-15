#include <stdint.h>
#include <string.h>

#include "lld.h"
#include "gde021a1.h"

#include "usbd_core.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "usbd_desc.h"

USBD_HandleTypeDef USBD_Device;

#define RED_LED GPIOA, 5
#define GREEN_LED GPIOB, 4

#define COLOR_SCL GPIOB, 6
#define COLOR_SDA GPIOB, 7
#define COLOR_INT GPIOB, 12

int main() {
    if (SysTick_Config(SystemCoreClock/1000)) {
        while(1);
    }
    rccEnableGPIOA();
    rccEnableGPIOB();

    gpioPinMode(GREEN_LED, gpioMode_output);
    gpioPinMode(RED_LED, gpioMode_output);

    USBD_Init(&USBD_Device, &VCP_Desc, 0);

    USBD_RegisterClass(&USBD_Device, &USBD_CDC);
    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
    USBD_Start(&USBD_Device);

    gde021a1Init();

    gde021a1Test();
    

    while(1){
        delay(500);
        gpioTogglePin(GREEN_LED);
    }

    return 0;
}