CC = arm-none-eabi-gcc

COMPILER_FLAGS = -c -mcpu=cortex-m0 -mthumb -std=gnu11 \
	-nostdlib \
	-I CMSIS/Device/ST/STM32G0xx/Include \
	-I CMSIS/Include

LINKER_FLAGS = -nostdlib -T stm32g0_ls.ld *.o -o 10_uart.elf -Wl,-Map=10_uart.map

final : 10_uart.elf

main.o : main.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

stm32g0_startup.o : stm32g0_startup.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

10_uart.elf : main.o stm32g0_startup.o
	$(CC) $(LINKER_FLAGS)

load :
	openocd -f board/st_nucleo_g0.cfg

clean:
	del -f *.o *.elf *.map
