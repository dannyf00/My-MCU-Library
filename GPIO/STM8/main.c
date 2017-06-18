#include "gpio.h"							//we use gpio
#include "delay.h"							//we use software delays
//#include "tim1.h"							//we use tim1
//#include "tim2.h"							//we use tim2
//#include "tim3.h"							//we use tim3
#include "tim4.h"							//we use tim4
#include "tim1oc.h"							//we use tim1 output compare
#include "tim2oc.h"							//we use tim2 output compare
#include "tim3oc.h"							//we use tim3 output compare
#include "adc1.h"							//we use adc1

//hardware configuration
#define LED_PORT		GPIOD
#define LED				(1<<0)
//end hardware configuration

//global defines

//global variables

uint8_t rand_get8(uint8_t ch) {
	uint8_t tmp;
	uint8_t i;
	for (i=0; i<8; i++) 
		tmp = (tmp << 1) | ((adc_read(ch)&0x01)?1:0);
	return tmp;
}

void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}

volatile uint8_t tmp;

void main(void) {
	mcu_init();								//reset the mcu
	IO_IN(LED_PORT, LED);
	IO_OUT(LED_PORT, LED);					//led1 as output
	tim3_init(1);
	//tim2_act(led_flp);
	tim3oc1_setpr(10000);
	tim3oc1_act(led_flp);
	tim3oc2_setpr(10000+100);
	tim3oc2_act(led_flp);
	adc_init();							//reset the adc
	ei();									//enable interrupt
	while (1) {
		//IO_FLP(LED_PORT, LED);			//start transmission
		//delay_ms(100);					//waste some time
		tmp = adc_read(ADC_AIN10);
		tmp = rand_get8(ADC_AIN0);
	};
}
