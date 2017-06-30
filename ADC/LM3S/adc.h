#ifndef ADC_H
#define ADC_H

#include "gpio.h"

//configuration
#define ADC0_SPEED				SYSCTL_ADCSPEED_250KSPS	//_1MSPS, _500KSPS, _250KSPS, _125KSPS
#define ADC0_SEQ				3			//ADC sequence number. [0..3]
#define ADC0_VREF				ADC_REF_INT				//_EXT_3V, _EXT_1V, _INT (default)
#define ADC1_SEQ				3			//ADC sequence number. [0..3]
//end configuration

typedef enum {
	AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN8, AIN9, AIN10, AIN11, AIN12,
	ATEMP,									//temperature sensor
	AINMAX
} AIN_TypeDef;

//convert 10-bit adc to temperature x 10, assuming Vref = 3v
#define Tx10(adc)				(1475 - ((75ul * (adc) * 30) >> 10))			//"3" = 3v, Vref_int

//initialize the adc
void adc0_init(void);

//read an adc ch
uint16_t adc0_read(AIN_TypeDef ch);

//select analog reference
void adc0_vrefset(uint32_t aref);

#endif
