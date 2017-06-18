#ifndef __DELAY_H
#define __DELAY_H

#include "gpio.h"				//we use f_cpu

void delay(volatile int dly);

void delay_us(volatile unsigned short us);

void delay_ms(volatile unsigned short ms);

#endif
