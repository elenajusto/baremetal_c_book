#include "spi.h"

void spi_gpio_init(void){
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/**** Set SPI1 pins to alternate function mode (MODER = 10) ****/

	// PA5 - SPI1_SCK
	GPIOA->MODER &= ~GPIO_MODER_MODER5_0;
	GPIOA->MODER |=  GPIO_MODER_MODER5_1;

	// PA6 - SPI1_MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6_0;
	GPIOA->MODER |=  GPIO_MODER_MODER6_1;

	// PA6 - Enable pull-up (PUPDR = 01) so idle line reads 0xFF
	GPIOA->PUPDR |=  GPIO_PUPDR_PUPD6_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD6_1;

	// PA7 - SPI1_MOSI
	GPIOA->MODER &= ~GPIO_MODER_MODER7_0;
	GPIOA->MODER |=  GPIO_MODER_MODER7_1;

	/**** Set CS pins ****/

	// Drive CS lines high (deselected) before making them outputs
	GPIOA->BSRR = GPIO_BSRR_BS9 | GPIO_BSRR_BS10;

	// Set PA9 to output (MODER = 01) - CS for Accelerometer
	GPIOA->MODER |=  GPIO_MODER_MODER9_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER9_1;

	// Set PA10 to output (MODER = 01) - CS for SD Card Module
	GPIOA->MODER |=  GPIO_MODER_MODER10_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER10_1;

	/**** Set PA5, PA6, PA7 to AF5 (SPI1) - AFRL nibble = 0101 ****/

	// PA5 - AF5 SPI1_SCK
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5;
	GPIOA->AFR[0] |=  (GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2);

	// PA6 - AF5 SPI1_MISO
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL6;
	GPIOA->AFR[0] |=  (GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2);

	// PA7 - AF5 SPI1_MOSI
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL7;
	GPIOA->AFR[0] |=  (GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_2);
}

void spi1_config(void){
	// Enable clock access to SPI1 module
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Set clock to fPCLK/64 (BR = 101) - slow start for SD init
	SPI1->CR1 &= ~SPI_CR1_BR_Msk;
	SPI1->CR1 |=  (SPI_SPEED_250KHZ << SPI_CR1_BR_Pos);

	// Set CPOL to 1 and CPHA to 1 (mode 3)
	SPI1->CR1 |=  SPI_CR1_CPHA;
	SPI1->CR1 |=  SPI_CR1_CPOL;

	// Enable full duplex
	SPI1->CR1 &= ~SPI_CR1_RXONLY;

	// Set MSB first
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

	// Set mode to MASTER
	SPI1->CR1 |=  SPI_CR1_MSTR;

	// Set 8 bit data mode
	SPI1->CR1 &= ~SPI_CR1_DFF;

	// Select software slave management
	SPI1->CR1 |=  SPI_CR1_SSM;
	SPI1->CR1 |=  SPI_CR1_SSI;

	// Enable SPI module
	SPI1->CR1 |=  SPI_CR1_SPE;
}

// SPI clock = fPCLK / 2^(br+1)   (br = 0..7, see SPI_SPEED_* in spi.h)
void spi1_set_speed(uint8_t br){
	// Wait until last transfer is finished
	while( (SPI1->SR & SPI_SR_BSY) ){
	}

	// Disable SPI before changing baud rate
	SPI1->CR1 &= ~SPI_CR1_SPE;

	// Clear BR bits and write new value
	SPI1->CR1 &= ~SPI_CR1_BR_Msk;
	SPI1->CR1 |=  ((br & 0x7U) << SPI_CR1_BR_Pos);

	// Re-enable SPI
	SPI1->CR1 |=  SPI_CR1_SPE;
}

// Send one byte and return the byte received at the same time
uint8_t spi1_transfer(uint8_t tx){
	// Wait until transmit buffer is empty
	while( !(SPI1->SR & SPI_SR_TXE) ){
	}

	// Write byte to data register - starts the 8 clock pulses
	SPI1->DR = tx;

	// Wait until the received byte has arrived
	while( !(SPI1->SR & SPI_SR_RXNE) ){
	}

	// Read received byte (this also clears RXNE)
	return (uint8_t)SPI1->DR;
}

void spi1_transmit(uint8_t *data, uint32_t size){
	uint32_t i = 0;

	while(i < size){
		// Wait until TXE is set
		while( !(SPI1->SR & SPI_SR_TXE) ){
		}

		// Write to data register
		SPI1->DR = data[i];
		i++;
	}

	// Wait until TXE is set
	while( !(SPI1->SR & SPI_SR_TXE) ){
	}

	// Wait for BUSY flag to reset
	while( (SPI1->SR & SPI_SR_BSY) ){
	}

	// Clear OVR flag
	(void)temp = SPI1->DR;
	(void)temp = SPI1->SR;
}

void spi1_receive(uint8_t *data, uint32_t size){
	while(size) {
		// Send dummy 0xFF and store the byte received at the same time
		*data++ = spi1_transfer(0xFF);
		size--;
	}
}

// ADXL345 chip select - PA9
void adxl_cs_enable(void){
	GPIOA->BSRR = GPIO_BSRR_BR9;	// PA9 low - select
}

void adxl_cs_disable(void){
	GPIOA->BSRR = GPIO_BSRR_BS9;	// PA9 high - deselect
}

// SD card chip select - PA10
void sd_cs_enable(void){
	GPIOA->BSRR = GPIO_BSRR_BR10;	// PA10 low - select
}

void sd_cs_disable(void){
	GPIOA->BSRR = GPIO_BSRR_BS10;	// PA10 high - deselect

	// Extra 8 clocks so the SD card releases MISO
	spi1_transfer(0xFF);
}
