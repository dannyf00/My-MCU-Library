//#include <stm32f0xx.h>							//we use f0
#include "gpio.h"									//we use gpio
#include "delay.h"									//we use delay
#include "systick.h"								//we use systick

//hardware configuration
#define LED_A			(1<<1)
#define LED_C			(1<<2)
//end hardware configuration

//global defines

//global variables


int main() {
	uint32_t tmp;
	mcu_init();										//reset the mcu
	IO_OUT(LED_PORT, LED_A); IO_SET(LED_PORT, LED_A);	//led as output
	IO_OUT(LED_PORT, LED_C); IO_CLR(LED_PORT, LED_C);
	systick_init(SYSTICK_1ms);
	while (1) {
		IO_FLP(LED_PORT, LED_A | LED_C);						//flip led
		tmp=systick_get();
		delay_ms(1000);								//waste some time
		tmp=systick_get()-tmp;
	}
	return 0;
}
