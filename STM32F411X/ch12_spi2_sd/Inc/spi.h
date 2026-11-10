#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>

#define SPI_SPEED_250KHZ	5U	// /64 -> 250 kHz, for SD init
#define SPI_SPEED_4MHZ		1U	// /4  -> 4 MHz, normal speed

void spi_gpio_init(void);
void spi1_config(void);
void spi1_set_speed(uint8_t br);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif
