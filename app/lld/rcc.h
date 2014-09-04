#ifndef RCC_H
#define RCC_H

#include "lld.h"

static inline void rccEnableIOPENR(uint32_t mask) {
    RCC->IOPENR |= mask;
}

static inline void rccDisableIOPENR(uint32_t mask) {
    RCC->IOPENR &= ~mask;
}

#define rccEnableGPIOA() rccEnableIOPENR(RCC_IOPENR_GPIOAEN)
#define rccEnableGPIOB() rccEnableIOPENR(RCC_IOPENR_GPIOBEN)
#define rccEnableGPIOC() rccEnableIOPENR(RCC_IOPENR_GPIOCEN)
#define rccEnableGPIOD() rccEnableIOPENR(RCC_IOPENR_GPIODEN)
#define rccEnableGPIOH() rccEnableIOPENR(RCC_IOPENR_GPIOHEN)

#define rccDisableGPIOA() rccDisableIOPENR(RCC_IOPENR_GPIOAEN)
#define rccDisableGPIOB() rccDisableIOPENR(RCC_IOPENR_GPIOBEN)
#define rccDisableGPIOC() rccDisableIOPENR(RCC_IOPENR_GPIOCEN)
#define rccDisableGPIOD() rccDisableIOPENR(RCC_IOPENR_GPIODEN)
#define rccDisableGPIOH() rccDisableIOPENR(RCC_IOPENR_GPIOHEN)

static inline void rccEnableAHBENR(uint32_t mask) {
    RCC->AHBENR |= mask;
}

static inline void rccDisableAHBENR(uint32_t mask) {
    RCC->AHBENR &= ~mask;
}

#define rccEnableDMA1() rccEnableAHBENR(RCC_AHBENR_DMA1EN)
#define rccEnableMIF() rccEnableAHBENR(RCC_AHBENR_MIFEN)
#define rccEnableCRC() rccEnableAHBENR(RCC_AHBENR_CRCEN)
#define rccEnableTSC() rccEnableAHBENR(RCC_AHBENR_TSCEN)
#define rccEnableRNG() rccEnableAHBENR(RCC_AHBENR_RNGEN)

#define rccDisableDMA1() rccDisableAHBENR(RCC_AHBENR_DMA1EN)
#define rccDisableMIF() rccDisableAHBENR(RCC_AHBENR_MIFEN)
#define rccDisableCRC() rccDisableAHBENR(RCC_AHBENR_CRCEN)
#define rccDisableTSC() rccDisableAHBENR(RCC_AHBENR_TSCEN)
#define rccDisableRNG() rccDisableAHBENR(RCC_AHBENR_RNGEN)

static inline void rccEnableAPB2ENR(uint32_t mask) {
    RCC->APB2ENR |= mask;
}

static inline void rccDisableAPB2ENR(uint32_t mask) {
    RCC->APB2ENR &= ~mask;
}

#define rccEnableSYSCFG() rccEnableAPB2ENR(RCC_APB2ENR_SYSCFGEN)
#define rccEnableTIM21() rccEnableAPB2ENR(RCC_APB2ENR_TIM21EN)
#define rccEnableTIM22() rccEnableAPB2ENR(RCC_APB2ENR_TIM22EN)
#define rccEnableMIFI() rccEnableAPB2ENR(RCC_APB2ENR_MIFIEN)
#define rccEnableADC1() rccEnableAPB2ENR(RCC_APB2ENR_ADC1EN)
#define rccEnableSPI1() rccEnableAPB2ENR(RCC_APB2ENR_SPI1EN)
#define rccEnableUSART1() rccEnableAPB2ENR(RCC_APB2ENR_USART1EN)
#define rccEnableDBGMCU() rccEnableAPB2ENR(RCC_APB2ENR_DBGMCUEN)

#define rccDisableSYSCFG() rccDisableAPB2ENR(RCC_APB2ENR_SYSCFGEN)
#define rccDisableTIM21() rccDisableAPB2ENR(RCC_APB2ENR_TIM21EN)
#define rccDisableTIM22() rccDisableAPB2ENR(RCC_APB2ENR_TIM22EN)
#define rccDisableMIFI() rccDisableAPB2ENR(RCC_APB2ENR_MIFIEN)
#define rccDisableADC1() rccDisableAPB2ENR(RCC_APB2ENR_ADC1EN)
#define rccDisableSPI1() rccDisableAPB2ENR(RCC_APB2ENR_SPI1EN)
#define rccDisableUSART1() rccDisableAPB2ENR(RCC_APB2ENR_USART1EN)
#define rccDisableDBGMCU() rccDisableAPB2ENR(RCC_APB2ENR_DBGMCUEN)

static inline void rccEnableAPB1ENR(uint32_t mask) {
    RCC->APB1ENR |= mask;
}

static inline void rccDisableAPB1ENR(uint32_t mask) {
    RCC->APB1ENR &= ~mask;
}

#define rccEnableTIM2() rccEnableAPB1ENR(RCC_APB1ENR_TIM2EN)
#define rccEnableTIM6() rccEnableAPB1ENR(RCC_APB1ENR_TIM6EN)
#define rccEnableLCD() rccEnableAPB1ENR(RCC_APB1ENR_LCDEN)
#define rccEnableWWDG() rccEnableAPB1ENR(RCC_APB1ENR_WWDGEN)
#define rccEnableSPI2() rccEnableAPB1ENR(RCC_APB1ENR_SPI2EN)
#define rccEnableUSART2() rccEnableAPB1ENR(RCC_APB1ENR_USART2EN)
#define rccEnableLPUART1() rccEnableAPB1ENR(RCC_APB1ENR_LPUART1EN)
#define rccEnableI2C1() rccEnableAPB1ENR(RCC_APB1ENR_I2C1EN)
#define rccEnableI2C2() rccEnableAPB1ENR(RCC_APB1ENR_I2C2EN)
#define rccEnableUSB() rccEnableAPB1ENR(RCC_APB1ENR_USBEN)
#define rccEnableCRS() rccEnableAPB1ENR(RCC_APB1ENR_CRSEN)
#define rccEnablePWR() rccEnableAPB1ENR(RCC_APB1ENR_PWREN)
#define rccEnableDAC() rccEnableAPB1ENR(RCC_APB1ENR_DACEN)
#define rccEnableLPTIM1() rccEnableAPB1ENR(RCC_APB1ENR_LPTIM1EN)

#define rccDisableTIM2() rccDisableAPB1ENR(RCC_APB1ENR_TIM2EN)
#define rccDisableTIM6() rccDisableAPB1ENR(RCC_APB1ENR_TIM6EN)
#define rccDisableLCD() rccDisableAPB1ENR(RCC_APB1ENR_LCDEN)
#define rccDisableWWDG() rccDisableAPB1ENR(RCC_APB1ENR_WWDGEN)
#define rccDisableSPI2() rccDisableAPB1ENR(RCC_APB1ENR_SPI2EN)
#define rccDisableUSART2() rccDisableAPB1ENR(RCC_APB1ENR_USART2EN)
#define rccDisableLPUART1() rccDisableAPB1ENR(RCC_APB1ENR_LPUART1EN)
#define rccDisableI2C1() rccDisableAPB1ENR(RCC_APB1ENR_I2C1EN)
#define rccDisableI2C2() rccDisableAPB1ENR(RCC_APB1ENR_I2C2EN)
#define rccDisableUSB() rccDisableAPB1ENR(RCC_APB1ENR_USBEN)
#define rccDisableCRS() rccDisableAPB1ENR(RCC_APB1ENR_CRSEN)
#define rccDisablePWR() rccDisableAPB1ENR(RCC_APB1ENR_PWREN)
#define rccDisableDAC() rccDisableAPB1ENR(RCC_APB1ENR_DACEN)
#define rccDisableLPTIM1() rccDisableAPB1ENR(RCC_APB1ENR_LPTIM1EN)

static inline void rccEnableIOPSMENR(uint32_t mask) {
    RCC->IOPSMENR |= mask;
}

static inline void rccDisableIOPSMENR(uint32_t mask) {
    RCC->IOPSMENR &= ~mask;
}

#define rccEnableGPIOASM() rccEnableIOPSMENR(RCC_IOPSMENR_GPIOASMEN)
#define rccEnableGPIOBSM() rccEnableIOPSMENR(RCC_IOPSMENR_GPIOBSMEN)
#define rccEnableGPIOCSM() rccEnableIOPSMENR(RCC_IOPSMENR_GPIOCSMEN)
#define rccEnableGPIODSM() rccEnableIOPSMENR(RCC_IOPSMENR_GPIODSMEN)
#define rccEnableGPIOHSM() rccEnableIOPSMENR(RCC_IOPSMENR_GPIOHSMEN)

#define rccDisableGPIOASM() rccDisableIOPSMENR(RCC_IOPSMENR_GPIOASMEN)
#define rccDisableGPIOBSM() rccDisableIOPSMENR(RCC_IOPSMENR_GPIOBSMEN)
#define rccDisableGPIOCSM() rccDisableIOPSMENR(RCC_IOPSMENR_GPIOCSMEN)
#define rccDisableGPIODSM() rccDisableIOPSMENR(RCC_IOPSMENR_GPIODSMEN)
#define rccDisableGPIOHSM() rccDisableIOPSMENR(RCC_IOPSMENR_GPIOHSMEN)

static inline void rccEnableAHBSMENR(uint32_t mask) {
    RCC->AHBSMENR |= mask;
}

static inline void rccDisableAHBSMENR(uint32_t mask) {
    RCC->AHBSMENR &= ~mask;
}

#define rccEnableDMA1SM() rccEnableAHBSMENR(RCC_AHBSMENR_DMA1SMEN)
#define rccEnableMIFSM() rccEnableAHBSMENR(RCC_AHBSMENR_MIFSMEN)
#define rccEnableSRAMSM() rccEnableAHBSMENR(RCC_AHBSMENR_SRAMSMEN)
#define rccEnableCRCSM() rccEnableAHBSMENR(RCC_AHBSMENR_CRCSMEN)
#define rccEnableTSCSM() rccEnableAHBSMENR(RCC_AHBSMENR_TSCSMEN)
#define rccEnableRNGSM() rccEnableAHBSMENR(RCC_AHBSMENR_RNGSMEN)

#define rccDisableDMA1SM() rccDisableAHBSMENR(RCC_AHBSMENR_DMA1SMEN)
#define rccDisableMIFSM() rccDisableAHBSMENR(RCC_AHBSMENR_MIFSMEN)
#define rccDisableSRAMSM() rccDisableAHBSMENR(RCC_AHBSMENR_SRAMSMEN)
#define rccDisableCRCSM() rccDisableAHBSMENR(RCC_AHBSMENR_CRCSMEN)
#define rccDisableTSCSM() rccDisableAHBSMENR(RCC_AHBSMENR_TSCSMEN)
#define rccDisableRNGSM() rccDisableAHBSMENR(RCC_AHBSMENR_RNGSMEN)

static inline void rccEnableAPB2SMENR(uint32_t mask) {
    RCC->APB2SMENR |= mask;
}

static inline void rccDisableAPB2SMENR(uint32_t mask) {
    RCC->APB2SMENR &= ~mask;
}

#define rccEnableSYSCFGSM() rccEnableAPB2SMENR(RCC_APB2SMENR_SYSCFGSMEN)
#define rccEnableTIM21SM() rccEnableAPB2SMENR(RCC_APB2SMENR_TIM21SMEN)
#define rccEnableTIM22SM() rccEnableAPB2SMENR(RCC_APB2SMENR_TIM22SMEN)
#define rccEnableADC1SM() rccEnableAPB2SMENR(RCC_APB2SMENR_ADC1SMEN)
#define rccEnableSPI1SM() rccEnableAPB2SMENR(RCC_APB2SMENR_SPI1SMEN)
#define rccEnableUSART1SM() rccEnableAPB2SMENR(RCC_APB2SMENR_USART1SMEN)
#define rccEnableDBGMCUSM() rccEnableAPB2SMENR(RCC_APB2SMENR_DBGMCUSMEN)

#define rccDisableSYSCFGSM() rccDisableAPB2SMENR(RCC_APB2SMENR_SYSCFGSMEN)
#define rccDisableTIM21SM() rccDisableAPB2SMENR(RCC_APB2SMENR_TIM21SMEN)
#define rccDisableTIM22SM() rccDisableAPB2SMENR(RCC_APB2SMENR_TIM22SMEN)
#define rccDisableADC1SM() rccDisableAPB2SMENR(RCC_APB2SMENR_ADC1SMEN)
#define rccDisableSPI1SM() rccDisableAPB2SMENR(RCC_APB2SMENR_SPI1SMEN)
#define rccDisableUSART1SM() rccDisableAPB2SMENR(RCC_APB2SMENR_USART1SMEN)
#define rccDisableDBGMCUSM() rccDisableAPB2SMENR(RCC_APB2SMENR_DBGMCUSMEN)

static inline void rccEnableAPB1SMENR(uint32_t mask) {
    RCC->APB1SMENR |= mask;
}

static inline void rccDisableAPB1SMENR(uint32_t mask) {
    RCC->APB1SMENR &= ~mask;
}

#define rccEnableTIM2SM() rccEnableAPB1SMENR(RCC_APB1SMENR_TIM2SMEN)
#define rccEnableTIM6SM() rccEnableAPB1SMENR(RCC_APB1SMENR_TIM6SMEN)
#define rccEnableLCDSM() rccEnableAPB1SMENR(RCC_APB1SMENR_LCDSMEN)
#define rccEnableWWDGSM() rccEnableAPB1SMENR(RCC_APB1SMENR_WWDGSMEN)
#define rccEnableSPI2SM() rccEnableAPB1SMENR(RCC_APB1SMENR_SPI2SMEN)
#define rccEnableUSART2SM() rccEnableAPB1SMENR(RCC_APB1SMENR_USART2SMEN)
#define rccEnableLPUART1SM() rccEnableAPB1SMENR(RCC_APB1SMENR_LPUART1SMEN)
#define rccEnableI2C1SM() rccEnableAPB1SMENR(RCC_APB1SMENR_I2C1SMEN)
#define rccEnableI2C2SM() rccEnableAPB1SMENR(RCC_APB1SMENR_I2C2SMEN)
#define rccEnableUSBSM() rccEnableAPB1SMENR(RCC_APB1SMENR_USBSMEN)
#define rccEnableCRSSM() rccEnableAPB1SMENR(RCC_APB1SMENR_CRSSMEN)
#define rccEnablePWRSM() rccEnableAPB1SMENR(RCC_APB1SMENR_PWRSMEN)
#define rccEnableDACSM() rccEnableAPB1SMENR(RCC_APB1SMENR_DACSMEN)
#define rccEnableLPTIM1SM() rccEnableAPB1SMENR(RCC_APB1SMENR_LPTIM1SMEN)

#define rccDisableTIM2SM() rccDisableAPB1SMENR(RCC_APB1SMENR_TIM2SMEN)
#define rccDisableTIM6SM() rccDisableAPB1SMENR(RCC_APB1SMENR_TIM6SMEN)
#define rccDisableLCDSM() rccDisableAPB1SMENR(RCC_APB1SMENR_LCDSMEN)
#define rccDisableWWDGSM() rccDisableAPB1SMENR(RCC_APB1SMENR_WWDGSMEN)
#define rccDisableSPI2SM() rccDisableAPB1SMENR(RCC_APB1SMENR_SPI2SMEN)
#define rccDisableUSART2SM() rccDisableAPB1SMENR(RCC_APB1SMENR_USART2SMEN)
#define rccDisableLPUART1SM() rccDisableAPB1SMENR(RCC_APB1SMENR_LPUART1SMEN)
#define rccDisableI2C1SM() rccDisableAPB1SMENR(RCC_APB1SMENR_I2C1SMEN)
#define rccDisableI2C2SM() rccDisableAPB1SMENR(RCC_APB1SMENR_I2C2SMEN)
#define rccDisableUSBSM() rccDisableAPB1SMENR(RCC_APB1SMENR_USBSMEN)
#define rccDisableCRSSM() rccDisableAPB1SMENR(RCC_APB1SMENR_CRSSMEN)
#define rccDisablePWRSM() rccDisableAPB1SMENR(RCC_APB1SMENR_PWRSMEN)
#define rccDisableDACSM() rccDisableAPB1SMENR(RCC_APB1SMENR_DACSMEN)
#define rccDisableLPTIM1SM() rccDisableAPB1SMENR(RCC_APB1SMENR_LPTIM1SMEN)

#endif