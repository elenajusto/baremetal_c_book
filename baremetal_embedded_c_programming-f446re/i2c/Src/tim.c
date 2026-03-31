#include "tim.h"

#define TIM2EN (1U<<0)
#define CR1_CEN (1U<<0)

void tim2_1hz_init(void) {
	/*Enable clock access to tim2*/
	RCC->APB1ENR |=TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1 ;		// System frequency / PSC -> 16 Mhz / 1599 = 10 Khz

	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;		// Time counters from 0 to 9999 (ARR/PSC = 10k / 10k Hz = 1 s)

	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}
