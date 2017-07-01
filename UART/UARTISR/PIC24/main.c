#include "config_c30.h"					//configuration words - for C30. Use config.h for XC16
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "systick.h"					//we use systick
#include "uart2.h"						//we use uart2
//#include "uart2isr.h"						//we use uart2

//hardware configuration
#define LED_PORT			PORTB
#define LED_DDR				TRISB
#define LED1				(1<<5)
#define LED2				(1<<4)
//end hardware configuration

//global defines

//global variables

char ustr[16];
int main(void) {
	uint32_t time0, time1;
	uint32_t tmp;

	mcu_init();							//reset the mcu
	IO_OUT(LED_DDR, LED1 | LED2);		//led as output
	systick_init();						//reset systick
	uart2_init(9600);					//reset uart1
	//uart2_init(9600);					//reset uart2
	while (1) {
		//IO_FLP(LED_PORT, LED1);		//flip led

		IO_SET(LED_PORT, LED1);
		if (!uart2_busy()) uart2_puts("12345678\n\r");	//send ustring
		IO_CLR(LED_PORT, LED1);

		//waste sometime
		systick_delayms(20);
	}
}
