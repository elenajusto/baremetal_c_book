CC = arm-none-eabi-gcc
COMPILER_FLAGS = -c -mcpu=cortex-m0 -mthumb -std=gnu11
LINKER_FLAGS = -nostdlib -T stm32g0_ls.ld *.o -o 6.1_periph.elf -Wl,-Map=6.1_periph.map

final : 6.1_periph.elf 

main.o : main.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

stm32g0_startup.o : stm32g0_startup.c
	$(CC) $(COMPILER_FLAGS) $^ -o $@

6.1_periph.elf : main.o stm32g0_startup.o
	$(CC) $(LINKER_FLAGS)

load :
	openocd -f board/st_nucleo_g0.cfg

clean:
	del -f *.o *.elf *.map