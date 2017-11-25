//#include <stm32f30x.h>
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
#include "gpio.h"					//we use own gpio macros

//set mode register;
//OTYPER takes default value (0x00->pushpull)
//OSPEEDR takes default value (0x00->low speed)
void GPIO_DDR(GPIO_TypeDef* port, uint16_t pins, uint16_t mode) {
	if (pins & (1ul <<  0)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 0 * 2))) | ((mode & GPIOMODE_AN) << ( 0 * 2));
	if (pins & (1ul <<  1)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 1 * 2))) | ((mode & GPIOMODE_AN) << ( 1 * 2));
	if (pins & (1ul <<  2)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 2 * 2))) | ((mode & GPIOMODE_AN) << ( 2 * 2));
	if (pins & (1ul <<  3)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 3 * 2))) | ((mode & GPIOMODE_AN) << ( 3 * 2));
	if (pins & (1ul <<  4)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 4 * 2))) | ((mode & GPIOMODE_AN) << ( 4 * 2));
	if (pins & (1ul <<  5)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 5 * 2))) | ((mode & GPIOMODE_AN) << ( 5 * 2));
	if (pins & (1ul <<  6)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 6 * 2))) | ((mode & GPIOMODE_AN) << ( 6 * 2));
	if (pins & (1ul <<  7)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 7 * 2))) | ((mode & GPIOMODE_AN) << ( 7 * 2));

	if (pins & (1ul <<  8)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 8 * 2))) | ((mode & GPIOMODE_AN) << ( 8 * 2));
	if (pins & (1ul <<  9)) port->MODER = (port->MODER & ~(GPIOMODE_AN << ( 9 * 2))) | ((mode & GPIOMODE_AN) << ( 9 * 2));
	if (pins & (1ul << 10)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (10 * 2))) | ((mode & GPIOMODE_AN) << (10 * 2));
	if (pins & (1ul << 11)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (11 * 2))) | ((mode & GPIOMODE_AN) << (11 * 2));
	if (pins & (1ul << 12)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (12 * 2))) | ((mode & GPIOMODE_AN) << (12 * 2));
	if (pins & (1ul << 13)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (13 * 2))) | ((mode & GPIOMODE_AN) << (13 * 2));
	if (pins & (1ul << 14)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (14 * 2))) | ((mode & GPIOMODE_AN) << (14 * 2));
	if (pins & (1ul << 15)) port->MODER = (port->MODER & ~(GPIOMODE_AN << (15 * 2))) | ((mode & GPIOMODE_AN) << (15 * 2));
}

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//set systemcoreclock to default hsi
//can only run at 8Mhz
void SystemCoreClockHSI(void) {

	SystemCoreClockUpdate();							//update SystemCoreClock
}

//set systemcoreclock to 8Mhz / 2 * RCC_PLLMul_x (x=[2..16])
//Need to check wait state
void SystemCoreClockHSIPLL(uint32_t RCC_PLLMul_x) {

	SystemCoreClockUpdate();							//update SystemCoreClock
}

//reset to hse
void SystemCoreClockHSE(void)
{
  
  SystemCoreClockUpdate();							//update system core clock
}

//reset to hse + pll
//RCC_PLLMul_x from RCC_PLLMul_2 to RCC_PLLMul_16
void SystemCoreClockHSEPLL(uint32_t RCC_PLLMul_x)
{
  
	SystemCoreClockUpdate();							//update system core clock
}

//reset the mcu
void mcu_init(void) {
	//RCC_DeInit();										//reset the clock - optional

	//Use one of the four four options
	//1. HSI
	//SystemCoreClockHSI();								//default - keep it here. size=4000-3996 = 4 bytes

	//2. HSIPLL
	//FLASH_SetLatency(FLASH_Latency_1);				//needed for 52Mhz or higher
	//SystemCoreClockHSIPLL_12Mhz();					//speed max out at 48Mhz. size=4004 - 3996 = 8 bytes

	//3. HSE
	//SystemCoreClockHSE();								//need capacitors on the crystal / fingers to get the oscillator started. size=4000-3996 = 4 bytes

	//4. HSEPLL
	//SystemCoreClockHSEPLL(RCC_PLLMul_2);				//need capacitors on the crystal / fingers to get the oscillator started. size=4000-3996 = 4 bytes

	//update system core clock
	//SystemCoreClockUpdate();							//update systemcoreclock
	
	//enable power to gpiox
	RCC->AHBENR |= 	RCC_AHBENR_GPIOAEN |
					RCC_AHBENR_GPIOBEN |
					RCC_AHBENR_GPIOCEN |
					RCC_AHBENR_GPIODEN |
					RCC_AHBENR_GPIOEEN |
					RCC_AHBENR_GPIOFEN |
					0x00;

	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);			//for button user
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);			//for leds
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);

}

