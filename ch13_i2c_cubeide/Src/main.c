// Microcontroller: STM32G071R
#include <stdio.h>
#include "uart.h"

int main(void) {
	// initalise debug uart
	uart_init();

	// initialise i2c
	i2c_init();
	
	// program loop
	while(1) {
		printf("atlas is best meow...\r\n");
	}
}
