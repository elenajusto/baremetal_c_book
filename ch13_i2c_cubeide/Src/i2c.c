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

    // set PB8 and PB9 alternate function to I2C - AF6
    // pin 9[3:0] - 7 6 5 4 - 0 1 1 0
    GPIOB->AFR[1] &= ~(1<<7);
    GPIOB->AFR[1] |= (1<<6);
    GPIOB->AFR[1] |= (1<<5);
    GPIOB->AFR[1] &= ~(1<<4);

    // pin 8[3:0] - 3 2 1 0 - 0 1 1 0
    GPIOB->AFR[1] &= ~(1<<3);
    GPIOB->AFR[1] |= (1<<2);
    GPIOB->AFR[1] |= (1<<1);
    GPIOB->AFR[1] &= ~(1<<0);

    // enable clock access to I2C1
    RCC->APBENR1 |= (1<<21);

    // enter I2C reset mode
    RCC->APBRSTR1 |= (1<<21);

    // exit I2C reset mode
    RCC->APBRSTR1 &= ~(1<<21);

    // set I2C peripheral clock - as per RM0444 page 951
    I2C1->TIMINGR  = (0x3 << 28);  // PRESC
    I2C1->TIMINGR |= (0x4 << 20);  // SCLDEL
    I2C1->TIMINGR |= (0x2 << 16);  // SDADEL
    I2C1->TIMINGR |= (0xF <<  8);  // SCLH
    I2C1->TIMINGR |= (0x13 << 0);  // SCLL

    // enable I2C1 module

}
