#ifndef _DAC_H
#define _DAC_H

#include "gpio.h"

//reset the dac
void dac_init(void);
//set the dac output -> lowest 5 bits effective
void dac_set(uint8_t out);
#endif
