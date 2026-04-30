// Microcontroller: STM32G071R
#include <stdint.h>

// GPIO Struct
typedef struct {
	volatile uint32_t MODER; 	// Offset: 0x00
	volatile uint32_t OTYPER; 	// Offset: 0x04
	volatile uint32_t OSPEEDR; 	// Offset: 0x08
	volatile uint32_t PUPDR; 	// Offset: 0x0C
	volatile uint32_t IDR; 		// Offset: 0x10
	volatile uint32_t ODR; 		// Offset: 0x14
	volatile uint32_t BSRR;		// Offset: 0x18
	volatile uint32_t LCKR; 	// Offset: 0x1C
	volatile uint32_t AFRL; 	// Offset: 0x20
	volatile uint32_t AFRH; 	// Offset: 0x24
} GPIO_TypeDef;

// RCC Struct
typedef struct {
	volatile uint32_t DUMMY[13]; // Padding to start at relevant offset
	volatile uint32_t IOPENR;	 // Offset: 0x34 - For STM32G07
} RCC_TypeDef;

// Base addresses
#define RCC_BASE	0x40021000	// For STM32G07
#define	GPIOA_BASE	0x50000000	// For STM32G07

// Peripheral pointer definitions
#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIO_TypeDef*) GPIOA_BASE)

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
		for (int i = 0; i < 500000; i++){}
	}
}






