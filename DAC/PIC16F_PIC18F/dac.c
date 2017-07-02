#include "dac.h"					//we use dac

//reset the dac
//Vdd/Vss as the rails
//Output not on a pin (DACOUT)
void dac_init(void) {
	DACEN = 0;						//disable the dac
	DACPSS1 = 0, DACPSS0 = 0;		//0b00->Vdd, 0b01->Vref+, 0b10->FVR1 output, 0b11->reserved
	DACLPS = 0;						//0->low power state selected
	DACOE = 0;						//0->dac output not connected to a pin; 1->dac otput connected to a pin
	DACNSS = 0;						//0->negative rail to Vss, 1->natative rail to Vref-
	DACEN = 1;						//enable dac
}


//set the dac output -> lowest 5 bits effective
void dac_set(uint8_t out) {
	DACCON1 = out;					//set the output
}
