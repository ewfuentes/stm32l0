#include "rcc.h"

void rccEnableHSI48(void) {
    SYSCFG->CFGR3 |= SYSCFG_CFGR3_EN_VREFINT | 
                     SYSCFG_CFGR3_ENREF_HSI48;
    while(!(SYSCFG->CFGR3 & SYSCFG_CFGR3_REF_HSI48_RDYF) && 
          !(SYSCFG->CFGR3 & SYSCFG_CFGR3_VREFINT_RDYF));

    RCC->CRRCR |= RCC_CRRCR_HSI48ON;
    while(!(RCC->CRRCR & RCC_CRRCR_HSI48RDY));
}