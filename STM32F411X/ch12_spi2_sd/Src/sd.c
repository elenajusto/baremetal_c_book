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
