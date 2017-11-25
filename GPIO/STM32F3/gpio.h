#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f30x.h"								//we use stm32f30x
//#include "stm32f30x_rcc.h"							//we use rcc
//#include "stm32f30x_gpio.h"							//we use gpio
//#include "stm32f30x_flash.h"							//we use flash

//port macros
#define IO_SET(port, pins) 	port->ODR |= (pins)		//port->BSRR = (pins)
#define IO_CLR(port, pins)	port->ODR &=~(pins)		//port->BRR = (pins)
#define IO_FLP(port, pins)	port->ODR ^= (pins)
#define IO_GET(port, pins)	(port->IDR & (pins))	//return gpio pins

//fast gpio routines
#define FIO_SET(port, pins)	port->BSRR = (pins)
#define FIO_CLR(port, pins)	port->BRR = (pins)
#define FIO_FLP(port, pins)	IO_FLP(port, pins)		//no fast io routine for pin flipping
#define FIO_GET(port, pins) IO_GET(port, pins)		// no fast io routines

//set pins to output
#define GPIOMODE_IN		0x00
#define GPIOMODE_OUT	0x01
#define GPIOMODE_AF		0x02
#define GPIOMODE_AN		0x03

void GPIO_DDR(GPIO_TypeDef* port, uint16_t pins, uint16_t mode);

#define IO_OUT(port, pins)	GPIO_DDR(port, pins, GPIOMODE_OUT)
#define IO_IN(port, pins)	GPIO_DDR(port, pins, GPIOMODE_IN)
#define IO_AF(port, pins)	GPIO_DDR(port, pins, GPIOMODE_AF)
#define IO_AN(port, pins)	GPIO_DDR(port, pins, GPIOMODE_AN)

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins);

//specific to STM32F3Discovery
//led definitions
#define LED_PORT		GPIOE
#define LED_DDR			GPIOE
#define LED3			(1<<9)
#define LED4			(1<<8)
#define LED5			(1<<10)
#define LED6			(1<<15)
#define LED7			(1<<11)
#define LED8			(1<<14)
#define LED9			(1<<12)
#define LED10			(1<<13)

//user button
#define BTN_PORT		GPIOA
#define BTN_DDR			GPIOA
#define BTN_USER		(1<<0)				//user button on gpioa.0

//electronic signatures for STM32F10x
/* Flash size */
#define F_SIZE         	(*((const unsigned short *) 0x1FFFF7E0))	//flash size, read-only
//unique IDs, read-only
#define U_ID			((const unsigned short *) 0x1FFFF7E8)		//U_ID95..0, referenced via U_ID[0], ..., U_ID[5]
#define U_ID0  	       	U_ID[0]										//(*((const unsigned short *) 0x1FFFF7E8))	//U_ID15..0
#define U_ID1			U_ID[1]										//(*((const unsigned short *) 0x1FFFF7EA))	//U_ID31..16
#define U_ID2         	U_ID[2]										//(*((const unsigned short *) 0x1FFFF7EC))	//U_ID47..32
#define U_ID3         	U_ID[3]										//(*((const unsigned short *) 0x1FFFF7EE))	//U_ID63..48
#define U_ID4         	U_ID[4]										//(*((const unsigned short *) 0x1FFFF7F0))	//U_ID79..64
#define U_ID5         	U_ID[5]										//(*((const unsigned short *) 0x1FFFF7F2))	//U_ID95..80

//set systemcoreclock to hsi
//can only run at 8Mhz
void SystemCoreClockHSI(void);
//set systemcoreclock to 8Mhz / 2 * RCC_PLLMul_x (x=[2..16])
//Need to check wait state RCC_PLLMul_2
void SystemCoreClockHSIPLL(uint32_t RCC_PLLMul_x);
#define SystemCoreClockHSIPLL_8Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_2)
#define SystemCoreClockHSIPLL_12Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_3)
#define SystemCoreClockHSIPLL_16Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_4)
#define SystemCoreClockHSIPLL_20Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_5)
#define SystemCoreClockHSIPLL_24Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_6)
#define SystemCoreClockHSIPLL_28Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_7)
#define SystemCoreClockHSIPLL_32Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_8)
#define SystemCoreClockHSIPLL_36Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_9)
#define SystemCoreClockHSIPLL_40Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_10)
#define SystemCoreClockHSIPLL_44Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_11)
#define SystemCoreClockHSIPLL_48Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_12)
#define SystemCoreClockHSIPLL_52Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_13)
#define SystemCoreClockHSIPLL_56Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_14)
#define SystemCoreClockHSIPLL_60Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_15)
#define SystemCoreClockHSIPLL_64Mhz()	SystemCoreClockHSIPLL(RCC_PLLMul_16)

//Caution: need to define HSE_VALUE in the pre-processor for the crystal used
//reset to hse
void SystemCoreClockHSE(void);
//reset to hse + pll
//RCC_PLLMul_x from RCC_PLLMul_2 to RCC_PLLMul_16
void SystemCoreClockHSEPLL(uint32_t RCC_PLLMul_x);


//reset the mcu
void mcu_init(void);


//nop
#define NOP()	__NOP()
#define NOP2()	{NOP(); NOP();}
#define NOP4()	{NOP2(); NOP2();}
#define NOP8()	{NOP4(); NOP4();}
#define NOP16()	{NOP8(); NOP8();}
#define NOP24()	{NOP16(); NOP8();}
#define NOP32()	{NOP16(); NOP16();}
#define NOP40()	{NOP32(); NOP8();}

//f_cpu speed
#define F_CPU				(SystemCoreClock/*24000000ul*/)					//cpu runs at 72Mhz at default

//void (*mcu_reset)(void) = 0x0000; 				//jump to 0x0000 -> software reset

#ifndef ei
#define ei()				__enable_irq()		//enable irq
#endif

#ifndef di
#define di()				__disable_irq()		//disable irq
#endif

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
#define PORTA				((volatile B16_TypeDef *) &(GPIOA->ODR))
#define PORTB				((volatile B16_TypeDef *) &(GPIOB->ODR))
#define PORTC				((volatile B16_TypeDef *) &(GPIOC->ODR))
#define PORTD				((volatile B16_TypeDef *) &(GPIOD->ODR))
#define PORTE				((volatile B16_TypeDef *) &(GPIOE->ODR))
#define PORTF				((volatile B16_TypeDef *) &(GPIOF->ODR))
#define PORTG				((volatile B16_TypeDef *) &(GPIOG->ODR))
#define PORTH				((volatile B16_TypeDef *) &(GPIOH->ODR))

//input register
#define PINA				((volatile B16_TypeDef *) &(GPIOA->IDR))
#define PINB				((volatile B16_TypeDef *) &(GPIOB->IDR))
#define PINC				((volatile B16_TypeDef *) &(GPIOC->IDR))
#define PIND				((volatile B16_TypeDef *) &(GPIOD->IDR))
#define PINE				((volatile B16_TypeDef *) &(GPIOE->IDR))
#define PINF				((volatile B16_TypeDef *) &(GPIOF->IDR))
#define PING				((volatile B16_TypeDef *) &(GPIOG->IDR))
#define PINH				((volatile B16_TypeDef *) &(GPIOH->IDR))

//input register
#define DDRA				((volatile B16_TypeDef *) &(GPIOA->DDR))
#define DDRB				((volatile B16_TypeDef *) &(GPIOB->DDR))
#define DDRC				((volatile B16_TypeDef *) &(GPIOC->DDR))
#define DDRD				((volatile B16_TypeDef *) &(GPIOD->DDR))
#define DDRE				((volatile B16_TypeDef *) &(GPIOE->DDR))
#define DDRF				((volatile B16_TypeDef *) &(GPIOF->DDR))
#define DDRG				((volatile B16_TypeDef *) &(GPIOG->DDR))
#define DDRH				((volatile B16_TypeDef *) &(GPIOH->DDR))


#endif
