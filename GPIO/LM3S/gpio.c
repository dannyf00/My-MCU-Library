//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_LM3S811						//indicate parts, for pin / memory definitions

#include "gpio.h"					//we use own gpio macros
//#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

uint32_t SystemCoreClock = 12000000ul;									//12Mhz default internal clock


//reset the mcu
void mcu_init(void) {

	//delay_ms(1000);					//short delay - in case the jtag / swd pins are locked up
	MAP_SysCtlDelay(F_CPU / 10);				//instead

	//
    // Set the clocking to run directly from the crystal.
    //
	//SystemCoreClockHSI_2Mhz();
	//SystemCoreClockHSE_25Mhz();
	SystemCoreClockHSE_40Mhz();
	
	//update systemcoreclock
	//SystemCoreClockUpdate();
	
	//enable the output
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOI);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

	//IO_IN(LED_PORT, LEDR | LEDG | LEDB);	//turn all leds off

	//update SystemCoreClock / F_CPU - incorrect results
	SystemCoreClock = MAP_SysCtlClockGet();		//is faulty?. MAP_SysCtlClockGet();
	
	ei();							//enable interrupt
}

