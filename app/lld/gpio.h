#ifndef GPIO_H
#define GPIO_H

#include "lld.h"

#define isGPIO(x) (x == GPIOA || x == GPIOB || \
                   x == GPIOC || x == GPIOD || x == GPIOH)

typedef enum {
    gpioMode_input,
    gpioMode_output,
    gpioMode_alternate,
    gpioMode_analog,
    gpioMode_count
} gpioMode_t;

typedef enum {
    gpioSpeed_verySlow,
    gpioSpeed_slow,
    gpioSpeed_medium,
    gpioSpeed_high,
    gpioSpeed_count
} gpioSpeed_t;

typedef enum {
    gpioPullUpDown_none,
    gpioPullUpDown_up,
    gpioPullUpDown_down,
    gpioPullUpDown_count,
}gpioPullUpDown_t;

typedef enum {
    gpioOutputType_pushPull,
    gpioOutputType_openDrain,
    gpioOutputType_count
} gpioOutputType_t;

static inline void gpioSetPin(GPIO_TypeDef *gpio, uint8_t pin) {
    assert(isGPIO(gpio));
    assert(pin < 16);

    gpio->BSRR |= 1 << pin;
}

static inline void gpioTogglePin(GPIO_TypeDef *gpio, uint8_t pin) {
    assert(isGPIO(gpio));
    assert(pin < 16);

    gpio->ODR ^= 1 << pin;
}

static inline void gpioResetPin(GPIO_TypeDef *gpio, uint8_t pin) {
    assert(isGPIO(gpio));
    assert(pin < 16);

    gpio->BRR |= 1 << pin;
}

static inline uint8_t gpioReadPin(GPIO_TypeDef *gpio, uint8_t pin) {
    assert(isGPIO(gpio));
    assert(pin < 16);

    return gpio->IDR & (1 << pin);
}

static inline void gpioPinMode(GPIO_TypeDef *gpio, uint8_t pin, 
                        uint8_t mode) {
    assert(isGPIO(gpio));
    assert(pin < 16);
    assert(mode < gpioMode_count);

    gpio->MODER &= ~(3 << (2 * pin));
    gpio->MODER |= mode << (2 * pin);
}

static inline void gpioAlternate(GPIO_TypeDef *gpio, uint8_t pin, uint8_t af) {
    assert(isGPIO(gpio));
    assert(pin < 16);
    assert(af < 8);
    assert((gpio == GPIOA) || 
           (gpio == GPIOB && af < 7) ||
           (gpio == GPIOC && af < 4) ||
           (gpio == GPIOD && af < 2) ||
           (gpio == GPIOH && af < 1));

    // There are two alternate function registers so we need to figure out
    // the index of the register we need to modify.  Furthermore, we need to 
    // figure out where in the register we need to set the mode
    uint8_t idx = pin / 8; // Integer division
    uint8_t shift = (pin % 8) * 4;

    gpio->AFR[idx] &= ~(0x0F << shift);
    gpio->AFR[idx] |= af << shift;

}

static inline void gpioOutputSpeed(GPIO_TypeDef *gpio, uint8_t pin,
                                   gpioSpeed_t speed) {
    assert(isGPIO(gpio));
    assert(pin < 16);
    assert(speed < gpioSpeed_count);

    gpio->OSPEEDR &= ~(3 << (2*pin));
    gpio->OSPEEDR |= speed << (2*pin);
}

static inline void gpioPullUpDown(GPIO_TypeDef *gpio, uint8_t pin,
                                   gpioPullUpDown_t mode) {
    assert(isGPIO(gpio));
    assert(pin < 16);
    assert(mode < gpioPullUpDown_count);

    gpio->PUPDR &= ~(3 << (2*pin));
    gpio->PUPDR |= mode << (2*pin);
}

static inline void gpioOutputType(GPIO_TypeDef *gpio, uint8_t pin,
                                    gpioOutputType_t mode) {
    assert(isGPIO(gpio));
    assert(pin < 16);
    assert(mode < gpioOutputType_count);

    uint32_t mask = 1 << pin;
    if (mode == gpioOutputType_pushPull) {
        gpio->OTYPER &= ~mask;
    } else if (mode == gpioOutputType_openDrain){
        gpio->OTYPER |= mask;
    }
}

#endif
