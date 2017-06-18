#include "gpio.h"							//we use gpio
#include "delay.h"							//we use software delays

//hardware configuration
#define LED_PORT		GPIOD
#define LED				(1<<0)
//end hardware configuration

//global defines

//global variables


void main(void) {
	mcu_init();								//reset the mcu
	IO_OUT(LED_PORT, LED);					//led1 as output
	ei();									//enable interrupt
	while (1) {
		IO_FLP(LED_PORT, LED);			//start transmission
		delay_ms(100);					//waste some time
	};
}
