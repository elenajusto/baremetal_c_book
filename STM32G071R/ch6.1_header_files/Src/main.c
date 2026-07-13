// Microcontroller: STM32G071R
#define STM32G071xx
#include "stm32g0xx.h"

// Bit mask
#define GPIOAEN		(1U<<0)		// Bit mask for GPIOA A bit 0
#define PIN5		(1U<<5)		// Bit mask for GPIOA A pin 5
#define LED_PIN		PIN5		// Alias for LED pin

// Main program
int main(void) {

	RCC->IOPENR |= GPIOAEN; 	// Enable clock access to GPIOA

	GPIOA->MODER |= (1U<<10); 	// Set bit 10 to 1
	GPIOA->MODER &= ~(1U<<11);	// Set bit 11 to 0
	
	// Main loop
	while(1) {

		// Toggle PA5
		GPIOA->ODR ^= LED_PIN;

		// Delay
		for (int i = 0; i < 1500000; i++){}
	}
}





