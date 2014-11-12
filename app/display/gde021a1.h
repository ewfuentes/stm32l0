#ifndef GDE021A1_H
#define GDE021A1_H

#include "lld.h"

#define PIXEL_HEIGHT 72
#define PIXEL_WIDTH 172

typedef enum {
    pixVal_black,
    pixVal_dgray,
    pixVal_lgray,
    pixVal_white,
    pixVal_cnt
} pixVal_t;

void gde021a1Init();

void drawScreenBuffer();

void setPixel(uint8_t x, uint8_t y, pixVal_t val);

void gde021a1Test();

#endif