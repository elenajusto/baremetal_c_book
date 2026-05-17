#define STM32G071xx
#include "stm32g0xx.h"

/*
    PB8 --- SCL
    PB9 --- SDA
*/

void i2c_init(void) {
    // enable clock access to GPIOB
    RCC->IOPENR |= (1<<1);    
    
    // set alternate function mode for PB8 and PB9
    GPIOB->MODER |= (1<<17);    // set 1
    GPIOB->MODER &= ~(1<<16);	// set 0

    GPIOB->MODER |= (1<<19);    // set 1
    GPIOB->MODER &= ~(1<<18);   // set 0

    // set PB8 and PB9 output type to open drain
    GPIOB->OTYPER |= (1<<8);
    GPIOB->OTYPER |= (1<<9);

    // enable pull up for PB8 and PB9
    GPIOB->PUPDR &= ~(1<<19);
    GPIOB->PUPDR |= (1<<18);

    GPIOB->PUPDR &= ~(1<<17);
    GPIOB->PUPDR |= (1<<16);

    // set PB8 and PB9 alternate function to I2C


    // enable clock access to I2C1


    // enter I2C reset mode


    // exit I2C reset mode


    // set I2C peripheral clock frequency


    // set I2C standard mode


    // set I2C rise time


    // enable I2C1 module

}
