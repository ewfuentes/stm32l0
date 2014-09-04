#include "gde021a1.h"

#define DISP_BUSY   GPIOA, 8
#define DISP_RESET  GPIOB, 2
#define DISP_DC     GPIOB, 11
#define DISP_CS     GPIOA, 15
#define DISP_SCK    GPIOB, 3
#define DISP_MOSI   GPIOB, 5
#define DISP_POWER  GPIOB, 10

#define  GDE021A1_EPD_PIXEL_WIDTH    ((uint16_t)172)
#define  GDE021A1_EPD_PIXEL_HEIGHT   ((uint16_t)18)

#define EPD_REG_0             0x00   /* Status Read */
#define EPD_REG_1             0x01   /* Driver Output Control */
#define EPD_REG_3             0x03   /* Gate driving voltage control */
#define EPD_REG_4             0x04   /* Source driving coltage control */
#define EPD_REG_7             0x07   /* Display Control */
#define EPD_REG_11            0x0B   /* Gate and Sorce non overlap period COntrol */
#define EPD_REG_15            0x0F   /* Gate scan start */
#define EPD_REG_16            0x10   /* Deep Sleep mode setting */
#define EPD_REG_17            0x11   /* Data Entry Mode Setting */
#define EPD_REG_18            0x12   /* SWRESET */
#define EPD_REG_26            0x1A   /* Temperature Sensor Control (Write to Temp Register) */
#define EPD_REG_27            0x1B   /* Temperature Sensor Control(Read from Temp Register) */
#define EPD_REG_28            0x1C   /* Temperature Sensor Control(Write Command  to Temp sensor) */
#define EPD_REG_29            0x1D   /* Temperature Sensor Control(Load temperature register with temperature sensor reading) */
#define EPD_REG_32            0x20   /* Master activation */
#define EPD_REG_33            0x21   /* Display update */
#define EPD_REG_34            0x22   /* Display update control 2 */
#define EPD_REG_36            0x24   /* write RAM */
#define EPD_REG_37            0x25   /* Read RAM */
#define EPD_REG_40            0x28   /* VCOM sense */
#define EPD_REG_41            0x29   /* VCOM Sense duration */
#define EPD_REG_42            0x2A   /* VCOM OTP program */
#define EPD_REG_44            0x2C   /* Write VCOMregister */
#define EPD_REG_45            0x2D   /* Read OTP registers */
#define EPD_REG_48            0x30   /* Program WS OTP */
#define EPD_REG_50            0x32   /* Write LUT register */
#define EPD_REG_51            0x33   /* Read LUT register */
#define EPD_REG_54            0x36   /* Program OTP selection */
#define EPD_REG_55            0x37   /* Proceed OTP selection */
#define EPD_REG_58            0x3A   /* Set dummy line pulse period */
#define EPD_REG_59            0x3B   /* Set Gate line width */
#define EPD_REG_60            0x3C   /* Select Border waveform */
#define EPD_REG_68            0x44   /* Set RAM X - Address Start / End Position */
#define EPD_REG_69            0x45   /* Set RAM Y - Address Start / End Position */
#define EPD_REG_78            0x4E   /* Set RAM X Address Counter */
#define EPD_REG_79            0x4F   /* Set RAM Y Address Counter */
#define EPD_REG_240           0xF0   /* Booster Set Internal Feedback Selection */
#define EPD_REG_255           0xFF   /* NOP */

// Look-up table for the epaper (90 bytes) 
const uint8_t WF_LUT[]={
  0x82, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00,
  0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0x00,
  0x55, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
  0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
  0xAA, 0xAA, 0xAA, 0xAA, 0x15, 0x15, 0x15, 0x15,
  0x05, 0x05, 0x05, 0x05, 0x01, 0x01, 0x01, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x41, 0x45, 0xF1, 0xFF, 0x5F, 0x55, 0x01, 0x00,
  0x00, 0x00};

SPI_TypeDef *dispSPI = SPI1;
static const uint32_t SPI_BAUDRATE = 500000;

// Prototypes
static void writeReg(uint8_t cmd, uint8_t data);
void gde021a1WriteRegArray(uint8_t cmd, uint8_t *data, uint8_t numDataBytes);

inline static void powerEnable() {
    gpioResetPin(DISP_POWER);
}

inline static void powerDisable() {
    gpioSetPin(DISP_POWER);
}

inline static void reset() {
    gpioResetPin(DISP_RESET);
    uint32_t i;
    for (i = 0; i < 0x0000FFFF; i++);
    gpioSetPin(DISP_RESET);
    for (i = 0; i < 0x0000FFFF; i++);
}

static void hwInit() {
    rccEnableGPIOA();
    rccEnableGPIOB();

    // Setup busy pin as input
    // This pin should be low before we try to send a command
    gpioPinMode(DISP_BUSY, gpioMode_input);
    gpioPullUpDown(DISP_BUSY, gpioPullUpDown_down);

    // Setup Reset pin
    // Active Low
    gpioPinMode(DISP_RESET, gpioMode_output);
    gpioSetPin(DISP_RESET);

    // Setup chip select pin
    gpioPinMode(DISP_CS, gpioMode_output);
    gpioSetPin(DISP_CS);

    // Setup Data/Command Pin
    gpioPinMode(DISP_DC, gpioMode_output);

    // Setup Power Pin
    gpioPinMode(DISP_POWER, gpioMode_output);

    // Setup SCK
    gpioPinMode(DISP_SCK, gpioMode_alternate);
    gpioAlternate(DISP_SCK, 0);
    gpioOutputSpeed(DISP_SCK, gpioSpeed_high);

    // Setup MOSI
    gpioPinMode(DISP_MOSI, gpioMode_alternate);
    gpioAlternate(DISP_MOSI, 0);
    gpioOutputSpeed(DISP_MOSI, gpioSpeed_high);

    // We don't need a MISO pin because the display is write only in SPI mode

    powerEnable();
    reset();
    spiInit(dispSPI, SPI_BAUDRATE);

}

void gde021a1Init() {
    hwInit();

    writeReg(EPD_REG_16, 0x00);     // Deep sleep mode disable
    writeReg(EPD_REG_17, 0x03);     // Data Entry Mode Setting

    // This sets the start and end addresses in the Y direction
    // RAM X address start = 0x00
    // RAM X address end = 0x11 (17 * 4 px/addr = 72 pixels)
    uint8_t temp[2] = {0x00, 0x11};
    gde021a1WriteRegArray(EPD_REG_68, temp, 2);
    
    // This sets the start and end addresses in the Y direction
    // RAM Y address start = 0x00
    // RAM Y address end = 0xAB
    temp[0] = 0x00;
    temp[1] = 0xAB;
    gde021a1WriteRegArray(EPD_REG_69, temp, 2);
    
    writeReg(EPD_REG_78, 0x00); // Set RAM X Address counter
    writeReg(EPD_REG_79, 0x00); // Set RAM Y Address counter
    writeReg(EPD_REG_240, 0x1F); // Booster Set Internal Feedback Selection
    writeReg(EPD_REG_33, 0x03); // Disable RAM bypass and set GS transition
                                // to GSA = GS0 and GSB = GS3
    writeReg(EPD_REG_44, 0xA0); // Write VCOM Register
    writeReg(EPD_REG_60, 0x64); // Border waveform
    gde021a1WriteRegArray(EPD_REG_50, (uint8_t *)WF_LUT, 90); //Write LUT
}

inline static void commandMode() {
    gpioResetPin(DISP_DC);
}

inline static void dataMode() {
    gpioSetPin(DISP_DC);
}

static inline void writeReg(uint8_t cmd, uint8_t data) {
    gde021a1WriteRegArray(cmd, &data, 1);
}

void gde021a1WriteRegArray(uint8_t cmd, uint8_t *data, uint8_t numDataBytes) {
    assert((numDataBytes > 0 && data != NULL) || 
           (numDataBytes == 0 && data == NULL));

    commandMode();
    spiSendReceive(dispSPI, 1, &cmd, NULL, DISP_CS);
    
    if (data != NULL) {
        dataMode();
        spiSendReceive(dispSPI, numDataBytes, data, NULL, DISP_CS);     
    }
   
}

static void refreshDisplay() {
    writeReg(EPD_REG_34, 0xC4);
    gde021a1WriteRegArray(EPD_REG_32, NULL, 0);
}

void gde021a1Test() {

    uint8_t i = 0;
    uint8_t row = 0;
    uint8_t col = 0;
    gde021a1WriteRegArray(EPD_REG_36, NULL, 0);
    dataMode();
    for (col = 0; col < 172; col++) {
        for (row = 0; row < 18; row++) {
            // Checkerboard
            if (((col / 2) % 2) < 1) {
                i = 0x0F;    
            } else {
                i = 0xF0;
            }

            // 4px bars
            if ((row % 2) > 0) {
                i = 0xFF;
            } else {
                i = 0x00;
            }
            // i = 0xFF;
            spiSendReceive(dispSPI,1, &i, NULL, DISP_CS);
            
        }
    }
    refreshDisplay();
}

