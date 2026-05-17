// Microcontroller: STM32G071R
#include <stdio.h>
#include "uart.h"

int main(void) {
	// initalise debug uart
	uart_init();

	// initialise i2c
	i2c_init();

	// trigger a single transaction to a dummy address just to see activity
    i2c1_byte_read(0x68, 0, 0);  // dummy address

	// program loop
	while(1) {
		printf("atlas is best meow...\r\n");
	}
}
