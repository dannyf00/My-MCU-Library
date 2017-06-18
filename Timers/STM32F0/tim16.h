#ifndef _TIM16_H
#define _TIM16_H

//#include "stm32f4xx_rcc.h"
//#include "stm32f10x_gpio.h"
#include "stm32f0xx_tim.h"					//we use timer
#include "stm32f0xx_misc.h"					//we use interrupt
#include "gpio.h"						//we use own macros

//tmr1 prescaler
#define TMR_PS_1x			1
#define TMR_PS_10x			10
#define TMR_PS_100x			100
#define TMR_PS_1000x			1000
#define TMR_PS_8x			8
#define TMR_PS_64x			64
#define TMR_PS_256x			256
#define TMR_PS_512x			512
#define TMR_PS_1024x			1024

//rtc timing constant
//some commented out due to overflow (_uint16_t)
//#define TMR_10000ms			(TMR_ms * 10000)	//1ms * 10000
//#define TMR_5000ms			(TMR_ms * 5000)		//1ms * 5000
//#define TMR_2000ms			(TMR_ms * 2000)		//1ms * 2000
//#define TMR_1000ms			(TMR_ms * 1000)		//1ms * 1000
//#define TMR_500ms			(TMR_ms * 500)		//1ms * 1000
//#define TMR_200ms			(TMR_ms * 200)		//1ms * 200
//#define TMR_100ms			(TMR_ms * 100)		//1ms * 100
//#define TMR_50ms			(TMR_ms * 50)		//1ms * 50
//#define TMR_20ms			(TMR_ms * 20)		//1ms * 20
//#define TMR_10ms			(TMR_ms * 10)		//1ms * 10
//#define TMR_5ms			(TMR_ms * 5)		//1ms * 5
#define TMR_2ms				(TMR_ms * 2)		//1ms * 2
#define TMR_1ms				(TMR_ms * 1)		//1ms * 1
#define TMR_500us			(TMR_ms / 2)		//1ms * 1
#define TMR_250us			(TMR_ms / 4)		//1ms * 1
#define TMR_100us			(TMR_ms / 10)		//1ms * 1
#define TMR_ms				(F_CPU / 1000)		//ms definition

//initialize the timer
//timer set to
void tmr16_init(uint16_t ps, uint16_t period);

//install user handler
void tmr16_act(void (*isr_ptr)(void));

#endif
