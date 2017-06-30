#include "adc.h"					//we use adc

//initialize the adc
void adc0_init(void) {
	//configure adc0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	//while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) continue;	//wait for peripheral to be ready
	SysCtlADCSpeedSet(ADC0_SPEED);									//set adc speed
	//ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, ADC_PS);    //ADC_SP [1..64]
	ADCReferenceSet(ADC0_BASE, ADC0_VREF);							//set reference to Vrefint
	//GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2);
    ADCSequenceDisable(ADC0_BASE, ADC0_SEQ);								//disable sequence before enabling it
    ADCSequenceConfigure(ADC0_BASE, ADC0_SEQ, ADC_TRIGGER_PROCESSOR, 0);	//configure sequency 0 to be initialized by the processor / software triggered
    //ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_END);			//configure sequence 0 to have ch0 as the only channel to be adc'd
    //ADCSequenceEnable(ADC0_BASE, 0);								//enable ADC0
    ADCIntClear(ADC0_BASE, 0);										//clear the int flag -> adc0 not finished
}

//adc conversion on ain channel using ADCn_BASE
//AIN0/PE3, AIN1/PE2, AIN2/PE1, AIN3/PE0, AIN4/PD3, AIN5/PD2,
//AIN6/PD1, AIN7/PD0, AIN8/PE5, AIN9/PE4, AIN10/PB4, AIN11/PB5
//ATEMP: Temperature sensor
//300ticks @ 1MSPS, 500ticks @ 125KSPS per read
uint16_t adc0_read(AIN_TypeDef ain) {
    unsigned long tmp;

    //make sure that adc isn't busy
    //while (ADCBusy(ADCn_BASE)) continue;

    //disable adc sequencing 0
    ADCSequenceDisable(ADC0_BASE, ADC0_SEQ);      //disable sequencing for ANALOGREAD
    //clear ADCInt flag
    ADCIntClear(ADC0_BASE, ADC0_SEQ);             //clear the flag
    switch (ain) {
	case AIN0:
	case AIN1:
	case AIN2:
	case AIN3:
	case AIN4:
	case AIN5:
	case AIN6:
	case AIN7:
	case AIN8:
	case AIN9:
	case AIN10:
	case AIN11:
	case AIN12:
		//add more if available on your chip
		//GPIOPinTypeADC(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH0 + ain - AIN0 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ATEMP:
	default:										//default to ATEMP
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
        break;
    //default: break;
    }
   	ADCSequenceEnable(ADC0_BASE, ADC0_SEQ);       		//enable the sequency
    ADCProcessorTrigger(ADC0_BASE, ADC0_SEQ);     		//start the conversion
    while (!ADCIntStatus(ADC0_BASE, ADC0_SEQ, false)) continue;   //wait for the conversion to finish
    ADCIntClear(ADC0_BASE, ADC0_SEQ);             		//clear the flag
    ADCSequenceDataGet(ADC0_BASE, ADC0_SEQ, &tmp);    	//obtain the adc reult
    return tmp;                                     //return the adc result
}

//select analog reference
void adc0_vrefset(uint32_t aref) {
	switch (aref) {
	case ADC_REF_INT:		ADCReferenceSet(ADC0_BASE, ADC_REF_INT); break;
	case ADC_REF_EXT_3V: 	ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V); break;		//use internal 3v reference
	case ADC_REF_EXT_1V: 	ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_1V); break;		//use internal 3v reference
	default: break;
	}
}

