#ifndef _TMR15_OC_H
#define _TMR15_OC_H

#include <stdint.h>
#include "gpio.h"

//calling convention
	//initialize the timer
	//tim15_init(1000/2);							//with a prescaler

	//initialize oc1 to call a user handler
	//tim15_setpr1(1000);							//specify period
	//tim15_act1(led_flp);							//install user handler
//end calling convention

//hardware configuration
//end hardware configuration

//global defines
//initialize tim2 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatability
void tim15_init(uint32_t ps);

//set tim15_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim15_setpr1(uint32_t pr);
//install user handler
void tim15_act1(void (*isr_ptr)(void));

//set tim15_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim15_setpr2(uint32_t pr);
//install user handler
void tim15_act2(void (*isr_ptr)(void));

//set tim15_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim15_setpr3(uint32_t pr);
//install user handler
void tim15_act3(void (*isr_ptr)(void));

//set tim15_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim15_setpr4(uint32_t pr);
//install user handler
void tim15_act4(void (*isr_ptr)(void));

#endif
