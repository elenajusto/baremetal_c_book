#include <stdio.h>
#include "uart.h"

int main(void) {
	// Init UART
	uart_init();

	while(1) {
		printf("meow\r\n");
	}
}
