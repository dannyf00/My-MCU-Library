//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_TM4C1233H6PM							//indicate parts, for pin / memory definitions
//#include "config.h"
#include "gpio.h"									//use gpio
#include "delay.h"									//use software delays
#include "systick.h"								//use systick
#include "tmr16.h"									//tmr in 16-bit mode

//hardware configuration
#define LED_PORT			GPIOC
#define LED					(1<<5)
#define LED_DLY				(F_CPU / 1000)
//end hardware configuration

//user isr
void led_flp(void) {
	IO_FLP(LED_PORT, LED);							//flip led
}

int main(void) {
	uint32_t i, tmp;
	volatile uint32_t time0, time1;
	
	mcu_init();										//reset the  mcu
	systick_init();									//reset systick
	tmp = F_CPU;
	
	IO_OUT(LED_PORT, LED);

	//set up tmr0a, 16bit
	tmr2b_init(1000, 50000);
	tmr2b_act(led_flp);
	ei();											//enable interrupts
	while(1) {
		//IO_FLP(LED_PORT, LED);					//flip the led
		//while (!tmr2b_ovfset()) continue;
		//tmr2b_ovfclr();

#if 0
		time0=ticks();
		systick_delayms(200);
		time1=ticks() - time0;
		//if (time1) time0=time0;
		NOP();
#endif
	}
	
	return 0;
}


