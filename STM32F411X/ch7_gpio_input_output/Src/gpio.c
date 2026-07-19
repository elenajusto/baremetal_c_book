#include "gpio.h"

#define GPIOAEN     (1U<<0)
#define LED_BS5     (1U<<5)     // bit set pin 5
#define LED_BR5     (1U<<21)    // bit reset pin 5 

void led_init(void) {
    // clock access to gpio a
    RCC->AHB1ENR |= GPIOAEN;

    // set pa5 to output mode
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &= ~(1U<<11);
}

void led_on(void) {
    // set pa5 high
    GPIOA->BSRR |= LED_BS5;
}

void led_off(void) {
    // set pa5 low
    GPIOA->BSRR |= LED_BR5;
}