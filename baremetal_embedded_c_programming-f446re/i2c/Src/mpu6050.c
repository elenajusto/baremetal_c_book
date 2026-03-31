#include "mpu6050.h"

// Variable to store single byte of data
char data;

// Buffer to store multiple bytes of data from the sensor
uint8_t data_buffer[6];


void sensor_init (void) {
	/*Enable I2C*/
	i2c1_init();

	/*Read address*/
	sensor_read_address(MPU_ADDR_DEFAULT);
}

void sensor_read_address (uint8_t reg) {
	i2c1_byte_read(MPU_ADDR_DEFAULT, reg, &data);
}
