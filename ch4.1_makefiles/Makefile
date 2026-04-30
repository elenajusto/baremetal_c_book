CC = arm-none-eabi-gcc
COMPILER_FLAGS = -c -mcpu=cortex-m0 -mthumb -std=gnu11
LINKER_FLAGS = -nostdlib -T stm32g0_ls.ld *.o -o 4.1_makefiles.elf -Wl,-Map=5_makefiles.map

final : 4.1_makefiles.elf 

main.o : main.c
	$(CC) $(COMPILER_FLAGS) main.c -o main.o

stm32g0_startup.o : stm32g0_startup.c
	$(CC) $(COMPILER_FLAGS) stm32g0_startup.c -o stm32g0_startup.o

4.1_makefiles.elf : main.o stm32g0_startup.o
	$(CC) $(LINKER_FLAGS)

load :
	openocd -f board/st_nucleo_g0.cfg

clean:
	del -f *.o *.elf *.map