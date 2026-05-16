#include <stdint.h>
#include "uart.h"

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define DEBUG_UART_BAUDRATE 115200
#define SYS_FREQ            16000000
#define APB1_CLK            SYS_FREQ
#define CR1_TE              (1U<<3)
#define CR1_UE              (1U<<0)
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

    // set PA2 to alternate function mode
    GPIOA->MODER &= ~(1U<<4);
    GPIOA->MODER |= (1U<<5);

    // set alternate function type to AF1 (USART2_TX)
    GPIOA->AFR[0] |=  (1U << 8);  

    // enable clock access to UART2
    RCC->APBENR1 |= UART2EN;

    // configure uart baudrate
    uart_set_baudrate(APB1_CLK, DEBUG_UART_BAUDRATE);

    // configure transfer direction
    USART2->CR1 = CR1_TE;

    // enable uart module
    USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch) {
    // make sure transmit data register is empty
    while (!(USART2->ISR & SR_TXE)) {}

    // write to transmit data register
    USART2->TDR = (ch & 0xFF);
}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate) {
    return( (periph_clk + (baudrate/2U)) / baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate) {
    USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}