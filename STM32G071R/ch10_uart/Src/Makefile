CC = arm-none-eabi-gcc

COMPILER_FLAGS = -c -mcpu=cortex-m0 -mthumb -std=gnu11 \
	-I CMSIS/Device/ST/STM32G0xx/Include \
	-I CMSIS/Include \
	-I Inc

LINKER_FLAGS = -nostartfiles -T stm32g0_ls.ld *.o -o 10_uart.elf -Wl,-Map=10_uart.map --specs=nosys.specs -lgcc

final : 10_uart.elf

main.o : Src/main.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

stm32g0_startup.o : stm32g0_startup.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

load :
	openocd -f board/st_nucleo_g0.cfg

clean:
	del -f *.o *.elf *.map

uart.o : Src/uart.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

10_uart.elf : main.o uart.o stm32g0_startup.o
	$(CC) $(LINKER_FLAGS)