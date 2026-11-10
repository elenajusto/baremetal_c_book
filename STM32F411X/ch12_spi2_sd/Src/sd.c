#include "sd.h"

// Wait until card releases MISO (reads 0xFF) = not busy
uint8_t sd_wait_ready(void){
	uint32_t timeout = SD_READY_TIMEOUT;

	while(timeout--){
		if( spi1_transfer(0xFF) == 0xFF ){
			return 1;	// Card ready
		}
	}
	return 0;			// Card time out
}


// Send a command frame and return the R1 response
uint8_t sd_send_cmd(uint8_t cmd, uint32_t arg, uint8_t crc){
	uint8_t r1;
	uint8_t n;

	// Wait until card is not busy
	if( !sd_wait_ready() ){
		return 0xFF;		// Return if no response
	}

	// Command frame: start + transmission bit (01) + 6-bit index
	spi1_transfer(0x40 | cmd);

	// 32-bit argument, MSB first
	spi1_transfer((uint8_t)(arg >> 24));
	spi1_transfer((uint8_t)(arg >> 16));
	spi1_transfer((uint8_t)(arg >> 8));
	spi1_transfer((uint8_t)arg);

	// CRC7 + end bit (only checked for CMD0 and CMD8)
	spi1_transfer(crc);

	// Response comes within 0-8 bytes; R1 always has bit 7 = 0
	n = SD_CMD_RESPONSE_TRIES;
	do {
		r1 = spi1_transfer(0xFF);
	} while( (r1 & 0x80) && --n );

	return r1;
}
