#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adxl345.h"
#include "sd.h"
#include "systick.h"

// Variables for storing accelerometer data
int16_t accel_x, accel_y, accel_z;
double accel_x_g, accel_y_g, accel_z_g;

uint8_t data_buffer[6];

int main(void) {
	uint8_t r1;

	uart_init();

	// SPI bus at 250 kHz for SD init
	spi_gpio_init();
	spi1_config();

	// Give the card time to power up
	systick_msec_delay(10);

	// 80 clocks with CS high so the card can start up
	for(int i = 0; i < 10; i++){
		spi1_transfer(0xFF);
	}

	// CMD0 with CS low: reset and enter SPI mode
	sd_cs_enable();
	r1 = sd_send_cmd(SD_CMD0, 0, 0x95);
	sd_cs_disable();

	printf("CMD0 R1: 0x%02X\n\r", r1);

	adxl_init();

	// Give time to read if success
	systick_msec_delay(5000);

	while(1) {
		// read accelerometer data
		adxl_read(ADXL345_REG_DATA_START, data_buffer);

		// combine high and low bytes to form full data
		accel_x = (uint16_t)( (data_buffer[1] << 8) | data_buffer[0]);
		accel_y = (uint16_t)( (data_buffer[3] << 8) | data_buffer[2]);
		accel_z = (uint16_t)( (data_buffer[5] << 8) | data_buffer[4]);

		// convert raw data to g
		accel_x_g = accel_x * 0.0078;
		accel_y_g = accel_y * 0.0078;
		accel_z_g = accel_z * 0.0078;

		// print values
		printf("accel_x: %d, accel_y: %d, accel_z: %d\n\r", accel_x, accel_y, accel_z);
//		printf("-------------------------------------\n\r");
//		printf("accel_x: %f, accel_y: %f, accel_z: %f\n\r", accel_x_g, accel_y_g, accel_z_g);
	}

	return 0;
}
