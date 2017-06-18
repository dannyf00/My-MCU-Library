#ifndef __DELAY_H
#define __DELAY_H

#include "gpio.h"				//we use _nop_()

void delay(unsigned int dly);

void delay_us(unsigned int us);

void delay_ms(unsigned int ms);

#endif //delay_h_
