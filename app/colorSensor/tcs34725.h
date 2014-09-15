#ifndef TCS34725_H
#define TCS34725_H

#include "lld.h"

void colorInit();

uint8_t colorRead(uint32_t *red, uint32_t *green, uint32_t *blue, 
                  uint32_t *lux);

#endif