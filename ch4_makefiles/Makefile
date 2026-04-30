final : 4_makefiles.elf 

main.o : main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -std=gnu11 main.c -o main.o

stm32g0_startup.o : stm32g0_startup.c
	arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -std=gnu11 stm32g0_startup.c -o stm32g0_startup.o

4_makefiles.elf : main.o stm32g0_startup.o
	arm-none-eabi-gcc -nostdlib -T stm32g0_ls.ld *.o -o 4_makefiles.elf -Wl,-Map=4_makefiles.map

load :
	openocd -f board/st_nucleo_g0.cfg

clean:
	del -f *.o *.elf *.map