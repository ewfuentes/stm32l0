#ifndef NXPSL3S_H
#define NXPSL3S_H

#include "lld.h"

#define RFID_DOWNLOAD_FLAG (1 << 15)
#define RFID_UPLOAD_FLAG (1 << 12)

void rfidInit();
uint16_t rfidReadConfig();
uint16_t rfidReadDownloadReg();
uint16_t rfidWriteDownloadReg(uint16_t data);

#endif