#include "gpio.h"
#include "systick.h"

bool btn_state;

int main(void) {
	// init led
	led_init();

	while(1) {
		systick_msec_delay(500);
		led_toggle();
	}
	
}
