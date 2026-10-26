#include "gpio.h"
#include "tim.h"

int main(void) {
	// init led
	led_init();

	// init timer
	tim2_1hz_init();

	// loop
	while(1) {
		// toggle led
		led_toggle();

		// wait uif
		while(!(TIM2->SR & SR_UIF)) {}

		// clear uif
		TIM2->SR &= ~(SR_UIF);
	}
}
