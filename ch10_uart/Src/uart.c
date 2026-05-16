#include <stm32g0xx.h>
#include <stdint.h>
#include "uart.h"

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define DEBUG_UART_BAUDRATE 115200
#define SYS_FREQ            16000000
#define APB1_CLK            SYS_FREQ
#define CR1_TE              (1U<<3)
#define CR1_UE              (1U<<13)
#define SR_TXE              (1U<<7)

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);

int __io_putchar(int ch) {
    uart_write(ch);
    return ch;
}

void uart_init(void) {
    // enable clock access to GPIOA
    RCC->IOPENR |= GPIOAEN;
}