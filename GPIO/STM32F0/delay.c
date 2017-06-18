#include <stm32f0Xx.h>
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
#include "gpio.h"							//we use f_cpu
#include "delay.h"							//we use software delay


#define DLY_MS	(14236/168)					//9184 for gcc/coide, 14236 for iar-arm and 8100 for gcc-arm @168Mhz on STM32F3 Discovery board

//delay a number of cycles
void delay(volatile uint8_t dly) {
	while (dly--) NOP();
}

//delay a few us
void delay_us(volatile uint16_t dly_us) {
	delay(dly_us);
	dly_us = dly_us >> 8;
	while (dly_us--) delay(0xff);			//delay(1);	//adjust dly_us for f_cpu
}

//delay a few ms
void delay_ms(volatile uint16_t dly_ms) {
	while (dly_ms--) delay_us(DLY_MS * (F_CPU / 1000000ul));
}

