#include <stdio.h>
#include <stdint.h>

// __Microcontroller__: STM32G071R

// Base address for peripherals
#define PERIPH_BASE         (0x40000000UL)

// Offset for AHB bus
#define AHB_OFFSET          (0x20000)

// Base address for AHB bus
#define AHB_BASE            (PERIPH_BASE + AHB_OFFSET)

// Base address for IOPORT peripherals
#define IOPORT_BASE         (0x50000000UL)

// Offset for GPIOA
#define GPIOA_OFFSET        (0x0000UL)

// Base address for GPIOA
#define GPIOA_BASE          (IOPORT_BASE + GPIOA_OFFSET)

// Offset for RCC
#define RCC_OFFSET          (0x1000UL)

// Base address for RCC
#define RCC_BASE            (AHB_BASE + RCC_OFFSET)

// Offset to RCC_IOPENR register
#define RCC_IOPENR_OFFSET   (0x34UL)

// Address of RCC_IOPENR register (raw address, no dereference for host testing)
#define RCC_IOPENR_ADDR     (RCC_BASE + RCC_IOPENR_OFFSET)

// Offset for GPIOA mode register
#define GPIOA_MODER_OFFSET  (0x00UL)

// Address for GPIOA mode register (raw address, no dereference for host testing)
#define GPIOA_MODER_ADDR    (GPIOA_BASE + GPIOA_MODER_OFFSET)

// Offset for GPIOA output data register
#define GPIOA_ODR_OFFSET    (0x14UL)

// Address for GPIOA output data register (raw address, no dereference for host testing)
#define GPIOA_ODR_ADDR      (GPIOA_BASE + GPIOA_ODR_OFFSET)

// __Bitmask__ to enable GPIOA (bit 0)
#define GPIOA_EN            (1U<<0)

// __Bitmask__ to select GPIOA pin 5
#define GPIOA_PIN5          (1U<<5)

// Alias for pin 5 representing LED pin
#define LED_PIN             GPIOA_PIN5

int main(void) {
    printf("--- Bus Bases ---\n");
    printf("PERIPH_BASE:       0x%08lX  (expect 0x40000000)\n", (unsigned long)PERIPH_BASE);
    printf("AHB_BASE:          0x%08lX  (expect 0x40020000)\n", (unsigned long)AHB_BASE);
    printf("IOPORT_BASE:       0x%08lX  (expect 0x50000000)\n", (unsigned long)IOPORT_BASE);

    printf("\n--- RCC ---\n");
    printf("RCC_BASE:          0x%08lX  (expect 0x40021000)\n", (unsigned long)RCC_BASE);
    printf("RCC_IOPENR_ADDR:   0x%08lX  (expect 0x40021034)\n", (unsigned long)RCC_IOPENR_ADDR);

    printf("\n--- GPIOA ---\n");
    printf("GPIOA_BASE:        0x%08lX  (expect 0x50000000)\n", (unsigned long)GPIOA_BASE);
    printf("GPIOA_MODER_ADDR:  0x%08lX  (expect 0x50000000)\n", (unsigned long)GPIOA_MODER_ADDR);
    printf("GPIOA_ODR_ADDR:    0x%08lX  (expect 0x50000014)\n", (unsigned long)GPIOA_ODR_ADDR);

    printf("\n--- Bitmasks ---\n");
    printf("GPIOA_EN:          0x%08X  (expect 0x00000001, bit 0)\n", GPIOA_EN);
    printf("GPIOA_PIN5:        0x%08X  (expect 0x00000020, bit 5)\n", GPIOA_PIN5);
    printf("LED_PIN:           0x%08X  (expect 0x00000020, same as GPIOA_PIN5)\n", LED_PIN);

    return 0;
}