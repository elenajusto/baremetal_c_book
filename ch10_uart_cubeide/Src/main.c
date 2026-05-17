// Microcontroller: STM32G071R
#include <stdio.h>
#include "uart.h"

int main(void) {
	// initalise debug uart
	uart_init();

	// program loop
	while(1) {
		printf("atlas is best meow...\r\n");
	}
}
