#ifndef _GPIO_H
#define _GPIO_H

//#include "inc/tm4c1233h6pm.h"		//for tivaware = lm4f120h5
//#include "inc/tm4c123gh6pm.h"		//for tivaware = lm4f120h5

#include <stdint.h>
#include <stdbool.h>
//#include "config.h"

//tivaware includes
//#define PART_LM3S811						//indicate parts, for pin / memory definitions
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
//#include "inc/hw_ints.h"
//#include "inc/hw_nvic.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"


extern uint32_t SystemCoreClock;					//set in mcu_init


//port macros
#define IO_SET(port, pins)		FIO_SET(port, pins)						//MAP_GPIOPinWrite(port, (pins), (pins))
#define IO_CLR(port, pins)		FIO_CLR(port, pins)						//MAP_GPIOPinWrite(port, (pins), (0))
#define IO_GET(port, pins)		FIO_GET(port, pins)						//MAP_GPIOPinRead(port, pins)
#define IO_FLP(port, pins)		MAP_GPIOPinWrite(port, (pins), ~IO_GET(port, pins))

//set pins as floating input
#define IO_IN(port, pins)		IO_INFL(port, pins)
#define IO_INFL(port, pins)		MAP_GPIOPinTypeGPIOInput(port, pins)
#define IO_INPU(port, pins)		do {IO_IN(port, pins); HWREG((port) + (GPIO_O_PUR)) |= (pins);} while (0)
#define IO_INPD(port, pins)		do {IO_IN(port, pins); HWREG((port) + (GPIO_O_PDR)) |= (pins);} while (0)
//set pins to output - clock assumed to be already pumped to the periopherals
#define IO_OUT(port, pins)		IO_OUTPP(port, pins)
#define IO_OUTPP(port, pins)	MAP_GPIOPinTypeGPIOOutput(port, pins)
//set pins as output OD
#define IO_OUTOD(port, pins)	do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_ODR)) |= (pins);} while (0)
#define IO_OUTPU(port, pins)	do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_PUR)) |= (pins);} while (0)
#define IO_OUTPD(port, pins)	do {IO_OUT(port, pins); HWREG((port) + (GPIO_O_PDR)) |= (pins);} while (0)

//fast gpio routines: approximately 3x faster than IO_XXX() macros above
#define FIO_SET(port, pins)		HWREG(port + (GPIO_O_DATA + ((pins) << 2))) = (pins)		//port->BSRR = (pins)
#define FIO_CLR(port, pins)		HWREG(port + (GPIO_O_DATA + ((pins) << 2))) = 0				//port->BRR = (pins)
#define FIO_FLP(port, pins)		HWREG(port + (GPIO_O_DATA + ((pins) << 2))) ^= (pins)		//IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) 	(HWREG(port + (GPIO_O_DATA + ((pins) << 2))) & (pins))		//IO_GET(port, pins)		// no fast io routines
#define FIO_OUT(port, pins)		IO_OUT(port, pins)
#define FIO_IN(port, pins)		IO_IN(port, pins)

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins);

#define GPIOA				GPIO_PORTA_BASE
#define GPIOB				GPIO_PORTB_BASE
#define GPIOC				GPIO_PORTC_BASE
#define GPIOD				GPIO_PORTD_BASE
#define GPIOE				GPIO_PORTE_BASE
#define GPIOF				GPIO_PORTF_BASE
#define GPIOI				GPIO_PORTI_BASE
#define GPIOJ				GPIO_PORTJ_BASE

//specific to LM3S811 EVK
//led definitions
#define LED_PORT			GPIOC
#define LED_DDR				GPIOC
#define LED					(1<<5)				//led on GPIOC5

//close sources
//HSI/PIOSC
#define SystemCoreClockHSI()		MAP_SysCtlClockSet(SYSCTL_SYSDIV_1  | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=16Mhz
#define SystemCoreClockHSI_1Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_16 | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=8Mhz
#define SystemCoreClockHSI_2Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_8  | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=8Mhz
#define SystemCoreClockHSI_4Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4  | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=8Mhz
#define SystemCoreClockHSI_8Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2  | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=8Mhz
#define SystemCoreClockHSI_16Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_1  | SYSCTL_USE_OSC | SYSCTL_OSC_INT);	//use PIOSC/HSI=16Mhz
#define SystemCoreClockHSI_10Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
#define SystemCoreClockHSI_20Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
#define SystemCoreClockHSI_25Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_8  | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
#define SystemCoreClockHSI_40Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_5  | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
//#define SystemCoreClockHSI_50Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4  | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
//#define SystemCoreClockHSI_80Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
//#define SystemCoreClockHSI_100Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2  | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
//#define SystemCoreClockHSI_200Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_1  | SYSCTL_USE_PLL | SYSCTL_OSC_INT);	//use PIOSC/HSI=20Mhz under PLL
//HSE/external crystal - for 6Mhz only - PLL looks to be 150Mhz on my chip
#define SystemCoreClockHSE()		MAP_SysCtlClockSet(SYSCTL_SYSDIV_6  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
#define SystemCoreClockHSE_1Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_6  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
#define SystemCoreClockHSE_2Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_3  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
#define SystemCoreClockHSE_3Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
//#define SystemCoreClockHSE_8Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
#define SystemCoreClockHSE_6Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_1  | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, no PLL
//#define SystemCoreClockHSE_10Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
//#define SystemCoreClockHSE_15Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
#define SystemCoreClockHSE_25Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_8  | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
#define SystemCoreClockHSE_40Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_5  | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
#define SystemCoreClockHSE_50Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4  | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
//#define SystemCoreClockHSE_80Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
//#define SystemCoreClockHSE_100Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_2  | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL
//#define SystemCoreClockHSE_200Mhz()	MAP_SysCtlClockSet(SYSCTL_SYSDIV_1  | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	//use PIOSC/HSI=6Mhz, use PLL

//reset the mcu
void mcu_init(void);

//nop
#define NOP()				__asm("nop")			//__asm("NOP")
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

//f_cpu speed
//#define SystemCoreClock		(SysCtlClockGet()/*40000000ul*/)					//cpu runs at 2Mhz -> Fxtal = 2Mhz
#define F_CPU				(SystemCoreClock)						//SysCtlClockGet() is faulty. Don't use					//cpu runs at 2Mhz -> Fxtal = 2Mhz
#define SystemCoreClockUpdate()	SystemCoreClock = SysCtlClockGet()				//for compatibility

//void (*mcu_reset)(void) = 0x0000; 							//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				IntMasterEnable()
#endif

#ifndef di
#define di()				IntMasterDisable()
#endif

//DID0/DID1
#define DID0				*(uint32_t *)SYSCTL_DID0			//DID0
#define DID1				*(uint32_t *)SYSCTL_DID1			//DID1

//simple multiples
#define x1(val)				(val)								//multiply val by 1
#define x2(val)				(((val) << 1))						//multiply val by 2
#define x3(val)				(x2(val) + (val))					//multiply val by 3
#define x4(val)				(((val) << 2))						//multiply val by 4
#define x5(val)				(x4(val) + (val))					//multiply val by 5
#define x6(val)				(x4(val) + x2(val))					//multiply val by 6
#define x7(val)				(x6(val) + (val))					//multiply val by 7
#define x8(val)				((val) << 3)						//multiply val by 8
#define x9(val)				(x8(val) + (val))					//multiply val by 9

//multiples of 10s
#define x10(val)			(x8(val) + x2(val))					//multiply val by 10
#define x100(val)			(x10(x10(val)))						//multiply val by 100
#define x1000(val)			(x100(x10(val)))					//multiply val by 1000
#define x1k(val)			x1000(val)							//multiply val by 1000
#define x10k(val)			(x100(x100(val)))					//multiply val by 10000

#define x20(val)			(x2(x10(val)))
#define x30(val)			(x3(x10(val)))
#define x40(val)			(x4(x10(val)))
#define x50(val)			(x5(x10(val)))
#define x60(val)			(x6(x10(val)))
#define x70(val)			(x7(x10(val)))
#define x80(val)			(x8(x10(val)))
#define x90(val)			(x9(x10(val)))

//multiples of 100s
#define x200(val)			(x2(x100(val)))
#define x300(val)			(x3(x100(val)))
#define x400(val)			(x4(x100(val)))
#define x500(val)			(x5(x100(val)))
#define x600(val)			(x6(x100(val)))
#define x700(val)			(x7(x100(val)))
#define x800(val)			(x8(x100(val)))
#define x900(val)			(x9(x100(val)))

//custom definitions
#define x34(val)			(x30(val) + x4(val))				//multiply val by 34
#define x97(val)			(x90(val) + x7(val))				//multiply val by 97x

//byte-bit definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
} B8_TypeDef;

//word definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
	volatile unsigned char B8:1;	//bit 8
	volatile unsigned char B9:1;	//bit 9
	volatile unsigned char B10:1;	//bit 10
	volatile unsigned char B11:1;	//bit 11
	volatile unsigned char B12:1;	//bit 12
	volatile unsigned char B13:1;	//bit 13
	volatile unsigned char B14:1;	//bit 14
	volatile unsigned char B15:1;	//bit 15
} B16_TypeDef;

//Dword definitions
typedef struct {
	volatile unsigned char B0:1;	//bit 0
	volatile unsigned char B1:1;	//bit 1
	volatile unsigned char B2:1;	//bit 2
	volatile unsigned char B3:1;	//bit 3
	volatile unsigned char B4:1;	//bit 4
	volatile unsigned char B5:1;	//bit 5
	volatile unsigned char B6:1;	//bit 6
	volatile unsigned char B7:1;	//bit 7
	volatile unsigned char B8:1;	//bit 8
	volatile unsigned char B9:1;	//bit 9
	volatile unsigned char B10:1;	//bit 10
	volatile unsigned char B11:1;	//bit 11
	volatile unsigned char B12:1;	//bit 12
	volatile unsigned char B13:1;	//bit 13
	volatile unsigned char B14:1;	//bit 14
	volatile unsigned char B15:1;	//bit 15
	volatile unsigned char B16:1;	//bit 16
	volatile unsigned char B17:1;	//bit 17
	volatile unsigned char B18:1;	//bit 18
	volatile unsigned char B19:1;	//bit 19
	volatile unsigned char B20:1;	//bit 20
	volatile unsigned char B21:1;	//bit 21
	volatile unsigned char B22:1;	//bit 22
	volatile unsigned char B23:1;	//bit 23
	volatile unsigned char B24:1;	//bit 24
	volatile unsigned char B25:1;	//bit 25
	volatile unsigned char B26:1;	//bit 26
	volatile unsigned char B27:1;	//bit 28
	volatile unsigned char B28:1;	//bit 28
	volatile unsigned char B29:1;	//bit 29
	volatile unsigned char B30:1;	//bit 30
	volatile unsigned char B31:1;	//bit 31
} B32_TypeDef;

//output register
#define PORTA				((volatile B16_TypeDef *) &((GPIOA) + (GPIO_O_DATA)))
#define PORTB				((volatile B16_TypeDef *) &((GPIOB) + (GPIO_O_DATA)))
#define PORTC				((volatile B16_TypeDef *) &((GPIOC) + (GPIO_O_DATA)))
#define PORTD				((volatile B16_TypeDef *) &((GPIOD) + (GPIO_O_DATA)))
#define PORTE				((volatile B16_TypeDef *) &((GPIOE) + (GPIO_O_DATA)))
#define PORTF				((volatile B16_TypeDef *) &((GPIOF) + (GPIO_O_DATA)))
#define PORTG				((volatile B16_TypeDef *) &((GPIOG) + (GPIO_O_DATA)))
#define PORTH				((volatile B16_TypeDef *) &((GPIOH) + (GPIO_O_DATA)))

//input register
#define PINA				((volatile B16_TypeDef *) &((GPIOA) + (GPIO_O_DATA)))
#define PINB				((volatile B16_TypeDef *) &((GPIOB) + (GPIO_O_DATA)))
#define PINC				((volatile B16_TypeDef *) &((GPIOC) + (GPIO_O_DATA)))
#define PIND				((volatile B16_TypeDef *) &((GPIOD) + (GPIO_O_DATA)))
#define PINE				((volatile B16_TypeDef *) &((GPIOE) + (GPIO_O_DATA)))
#define PINF				((volatile B16_TypeDef *) &((GPIOF) + (GPIO_O_DATA)))
#define PING				((volatile B16_TypeDef *) &((GPIOG) + (GPIO_O_DATA)))
#define PINH				((volatile B16_TypeDef *) &((GPIOH) + (GPIO_O_DATA)))

//input register
#define DDRA				((volatile B16_TypeDef *) &((GPIOA) + (GPIO_O_DIR)))
#define DDRB				((volatile B16_TypeDef *) &((GPIOB) + (GPIO_O_DIR)))
#define DDRC				((volatile B16_TypeDef *) &((GPIOC) + (GPIO_O_DIR)))
#define DDRD				((volatile B16_TypeDef *) &((GPIOD) + (GPIO_O_DIR)))
#define DDRE				((volatile B16_TypeDef *) &((GPIOE) + (GPIO_O_DIR)))
#define DDRF				((volatile B16_TypeDef *) &((GPIOF) + (GPIO_O_DIR)))
#define DDRG				((volatile B16_TypeDef *) &((GPIOG) + (GPIO_O_DIR)))
#define DDRH				((volatile B16_TypeDef *) &((GPIOH) + (GPIO_O_DIR)))

#endif
