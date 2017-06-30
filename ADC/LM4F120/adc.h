#ifndef ADC_H_
#define ADC_H_

#include "gpio.h"							//we use gpio

//adc configuration
#define ADC0_SEQ			3				//adc sequence 3 (single ch)
#define ADC1_SEQ			3				//adc sequence 3 (single ch)

#define ADC0_PS				64				//adc prescaler, [1..64]
#define ADC1_PS				64				//adc prescaler, [1..64]
//end adc configuration

//global defines
//adc channels
#define ADC_CH0				ADC_CTL_CH0
#define ADC_CH1				ADC_CTL_CH1
#define ADC_CH2				ADC_CTL_CH2
#define ADC_CH3				ADC_CTL_CH3
#define ADC_CH4				ADC_CTL_CH4
#define ADC_CH5				ADC_CTL_CH5
#define ADC_CH6				ADC_CTL_CH6
#define ADC_CH7				ADC_CTL_CH7
#define ADC_CH8				ADC_CTL_CH8
#define ADC_CH9				ADC_CTL_CH9
#define ADC_CH10			ADC_CTL_CH10
#define ADC_CH11			ADC_CTL_CH11
#define ADC_TS				ADC_CTL_TS		//temperature sensor

//adc reference voltage
#define ADC_VREF_INT		ADC_REF_INT
#define ADC_VREF_EXT		ADC_REF_EXT_3V

//12-bit adc on the temperature sensor, from adc to temp x 10
#define Tx10(adc)				(1475 - ((75ul * (adc) * 30) >> 12))			//"3" = 3v, Vref_int

void adc0_init(void);
void adc1_init(void);

uint32_t adc0_read(uint32_t ain);
uint32_t adc1_read(uint32_t ain);

void adc0_setvref(uint32_t vref);
void adc1_setvref(uint32_t vref);

#endif /* ADC_H_ */
