#include "adc.h"					//we use adc


//reset the adc0
void adc0_init(void) {
	//configure adc0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) continue;	//wait for peripheral to be ready
	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, ADC0_PS);    //ADC_SP [1..64]
	ADCReferenceSet(ADC0_BASE, ADC_REF_INT);						//set reference to Vrefint
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
uint32_t adc0_read(uint32_t ain) {
    uint32_t tmp;

    //make sure that adc isn't busy
	//while (ADCBusy(ADCn_BASE)) continue;

    //disable adc sequencing 0
    ADCSequenceDisable(ADC0_BASE, ADC0_SEQ);      //disable sequencing for ANALOGREAD
    //clear ADCInt flag
    ADCIntClear(ADC0_BASE, ADC0_SEQ);             //clear the flag
    switch (ain) {
    case ADC_CH0:
        //ADC_CH0 = PE3
		GPIOPinTypeADC(GPIOE, 1<<3);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH1:
        //ADC_CH1 = PE2
		GPIOPinTypeADC(GPIOE, 1<<2);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH2:
        //ADC_CH2 = PE1
		GPIOPinTypeADC(GPIOE, 1<<1);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH3:
        //ADC_CH3 = PE0
		GPIOPinTypeADC(GPIOE, 1<<0);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH4:
        //ADC_CH4 = PD3
		GPIOPinTypeADC(GPIOD, 1<<3);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH4 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH5:
        //ADC_CH5 = PD2
		GPIOPinTypeADC(GPIOD, 1<<2);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH5 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH6:
        //ADC_CH6 = PD1
		GPIOPinTypeADC(GPIOD, 1<<1);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH6 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH7:
        //ADC_CH7 = PD0
		GPIOPinTypeADC(GPIOD, 1<<0);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH8:
        //ADC_CH8 = PE5
		GPIOPinTypeADC(GPIOE, 1<<5);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH9:
        //ADC_CH9 = PE4
		GPIOPinTypeADC(GPIOE, 1<<4);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH10:
        //ADC_CH10 = PB4
		GPIOPinTypeADC(GPIOB, 1<<4);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH10 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH11:
        //ADC_CH11 = PB5
		GPIOPinTypeADC(GPIOB, 1<<5);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
        break;
    default:														//default: read Temperature sensor
    case ADC_TS:
        ADCSequenceStepConfigure(ADC0_BASE, ADC0_SEQ, 0, ADC_CTL_TS  | ADC_CTL_IE | ADC_CTL_END);
        break;
    }
   	ADCSequenceEnable(ADC0_BASE, ADC0_SEQ);       		//enable the sequency
    ADCProcessorTrigger(ADC0_BASE, ADC0_SEQ);     		//start the conversion
    while (!ADCIntStatus(ADC0_BASE, ADC0_SEQ, false)) continue;   //wait for the conversion to finish
    ADCIntClear(ADC0_BASE, ADC0_SEQ);             		//clear the flag
    ADCSequenceDataGet(ADC0_BASE, ADC0_SEQ, &tmp);    	//obtain the adc reult
    return tmp;                                     	//return the adc result
}


//select analog reference
void adc0_setvref(uint32_t aref) {
	switch (aref) {
	case ADC_VREF_EXT: ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V); break;	//use external 3v reference
	default:
	case ADC_VREF_INT: ADCReferenceSet(ADC0_BASE, ADC_REF_INT); break;		//use internal 3v reference
	}
}

//reset the adc1
void adc1_init(void) {
	//configure adc0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1)) continue;	//wait for peripheral to be ready
	ADCClockConfigSet(ADC1_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, ADC1_PS);    //ADC_SP [1..64]
	ADCReferenceSet(ADC1_BASE, ADC_REF_INT);						//set reference to Vrefint
	//GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2);
    ADCSequenceDisable(ADC1_BASE, ADC1_SEQ);								//disable sequence before enabling it
    ADCSequenceConfigure(ADC1_BASE, ADC1_SEQ, ADC_TRIGGER_PROCESSOR, 0);	//configure sequency 0 to be initialized by the processor / software triggered
    //ADCSequenceStepConfigure(ADC1_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_END);			//configure sequence 0 to have ch0 as the only channel to be adc'd
    //ADCSequenceEnable(ADC1_BASE, 0);								//enable ADC1
    ADCIntClear(ADC1_BASE, 0);										//clear the int flag -> adc0 not finished

}

//adc conversion on ain channel using ADCn_BASE
//AIN0/PE3, AIN1/PE2, AIN2/PE1, AIN3/PE0, AIN4/PD3, AIN5/PD2,
//AIN6/PD1, AIN7/PD0, AIN8/PE5, AIN9/PE4, AIN10/PB4, AIN11/PB5
//ATEMP: Temperature sensor
uint32_t adc1_read(uint32_t ain) {
    uint32_t tmp;

    //make sure that adc isn't busy
	//while (ADCBusy(ADCn_BASE)) continue;

    //disable adc sequencing 0
    ADCSequenceDisable(ADC1_BASE, ADC1_SEQ);      //disable sequencing for ANALOGREAD
    //clear ADCInt flag
    ADCIntClear(ADC1_BASE, ADC1_SEQ);             //clear the flag
    switch (ain) {
    case ADC_CH0:
        //ADC_CH0 = PE3
		GPIOPinTypeADC(GPIOE, 1<<3);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH1:
        //ADC_CH1 = PE2
		GPIOPinTypeADC(GPIOE, 1<<2);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH2:
        //ADC_CH2 = PE1
		GPIOPinTypeADC(GPIOE, 1<<1);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH3:
        //ADC_CH3 = PE0
		GPIOPinTypeADC(GPIOE, 1<<0);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH3 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH4:
        //ADC_CH4 = PD3
		GPIOPinTypeADC(GPIOD, 1<<3);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH4 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH5:
        //ADC_CH5 = PD2
		GPIOPinTypeADC(GPIOD, 1<<2);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH5 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH6:
        //ADC_CH6 = PD1
		GPIOPinTypeADC(GPIOD, 1<<1);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH6 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH7:
        //ADC_CH7 = PD0
		GPIOPinTypeADC(GPIOD, 1<<0);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH8:
        //ADC_CH8 = PE5
		GPIOPinTypeADC(GPIOE, 1<<5);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH8 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH9:
        //ADC_CH9 = PE4
		GPIOPinTypeADC(GPIOE, 1<<4);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH10:
        //ADC_CH10 = PB4
		GPIOPinTypeADC(GPIOB, 1<<4);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH10 | ADC_CTL_IE | ADC_CTL_END);
        break;
    case ADC_CH11:
        //ADC_CH11 = PB5
		GPIOPinTypeADC(GPIOB, 1<<5);
        //configure adc sequency
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
        break;
    default:														//default: read Temperature sensor
    case ADC_TS:
        ADCSequenceStepConfigure(ADC1_BASE, ADC1_SEQ, 0, ADC_CTL_TS  | ADC_CTL_IE | ADC_CTL_END);
        break;
    }
   	ADCSequenceEnable(ADC1_BASE, ADC1_SEQ);       		//enable the sequency
    ADCProcessorTrigger(ADC1_BASE, ADC1_SEQ);     		//start the conversion
    while (!ADCIntStatus(ADC1_BASE, ADC1_SEQ, false)) continue;   //wait for the conversion to finish
    ADCIntClear(ADC1_BASE, ADC1_SEQ);             		//clear the flag
    ADCSequenceDataGet(ADC1_BASE, ADC1_SEQ, &tmp);    	//obtain the adc reult
    return tmp;                                     	//return the adc result
}


//select analog reference
void adc1_setvref(uint32_t aref) {
	switch (aref) {
	case ADC_VREF_EXT: ADCReferenceSet(ADC1_BASE, ADC_REF_EXT_3V); break;	//use external 3v reference
	default:
	case ADC_VREF_INT: ADCReferenceSet(ADC1_BASE, ADC_REF_INT); break;		//use internal 3v reference
	}
}

