#ifndef SD_H_
#define SD_H_

#include "spi.h"

/**** SD card commands - SPI mode ****/
#define SD_CMD0		0	// GO_IDLE_STATE 		- Software reset
#define SD_CMD8		8	// SEND_IF_COND 		- For only SDC V2. Check voltage range
#define SD_CMD17	17	// READ_SINGLE_BLOCK 	- Read a block
#define SD_CMD24	24	// WRITE_BLOCK 			- Write a block
#define SD_CMD55	55	// APP_CMD 				- Leading command of ACMD<n> command
#define SD_CMD58	58	// READ_OCR 			- Read OCR
#define SD_ACMD41	41	// APP_SEND_OP_COND 	- For only SDC. Initiate initialization process (send CMD55 first)

#define SD_READY_TIMEOUT	200000	// max 0xFF reads in sd_wait_ready() (~0.5 s at 4 MHz)

uint8_t sd_wait_ready(void);

#endif
