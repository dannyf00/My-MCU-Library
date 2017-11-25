//#include <stm32f0xx.h>						//we use f0
#include "gpio.h"								//we use gpio
#include "delay.h"								//we use delay
#include "systick.h"							//we use systick
#include "coretick.h"

//hardware configuration
//end hardware configuration

//global defines

//global variable
uint32_t tmp;

int main(void) {
	mcu_init();									//reset the  mcu
	coretick_init();
	systick_init();								//initialize systick
	tmp=F_CPU;									//read f_cpu - for debugging
	IO_OUT(LED_PORT, LED3 | LED4);				//led3/4 as output
	ei();
	while (1) {
		IO_FLP(LED_PORT, LED3 | LED4);			//flip led3/4
		tmp=coreticks();
		delay_ms(1000);							//waste some time
		tmp=coreticks()-tmp;
	};
}
