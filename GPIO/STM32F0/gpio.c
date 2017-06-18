//#include <stm32f0xx.h>
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
#include "gpio.h"					//we use own gpio macros

//set pins to output
//port = GPIOA..x, as the chip may support
void IO_OUTPP(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}
//set pins as output, open drain
void IO_OUTOD(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}
//set pins as output, pull-up
void IO_OUTPU(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}
//set pins as output, pull-down
void IO_OUTPD(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}
//set pins as alternate function
void IO_AF(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}
//set pins as analog input
void IO_AN(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_0..15 + GPIO_Pin_All
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;		//GPIO_Mode_Out_PP -> push-pull; GPIO_Mode_Out_OD -> open drain
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;		//_PP for push-pull. _OD for open drain
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for no pull-up or -down
	GPIO_Init(port, &GPIO_InitStruct);
}

//set pins as floating input
void IO_INFL(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN/*_FLOATING*/;	//GPIO_Mode_IN_FLOATING -> input, floating; GPIO_Mode_IN_IPU/IPD -> input, pull-up / pull-down
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//_UP for pull-up, _DOWN for pull-down. _NOPULL for floating
	GPIO_Init(port, &GPIO_InitStruct);
}

void IO_INPU(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN/*_FLOATING*/;	//GPIO_Mode_IN_FLOATING -> input, floating; GPIO_Mode_IN_IPU/IPD -> input, pull-up / pull-down
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for floating
	GPIO_Init(port, &GPIO_InitStruct);
}

void IO_INPD(GPIO_TypeDef* port, uint16_t pins) {
	GPIO_InitTypeDef        GPIO_InitStruct;

	/* Configure PC8 and PC9 in output pushpull mode */
	GPIO_InitStruct.GPIO_Pin = pins;				//GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN/*_FLOATING*/;	//GPIO_Mode_IN_FLOATING -> input, floating; GPIO_Mode_IN_IPU/IPD -> input, pull-up / pull-down
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	//GPIO_Speed_50Mhz -> 50Mhz; GPIO_Speed_2Mhz -> 2Mhz; GPIO_Speed_10Mhz -> 10Mhz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;		//_UP for pull-up, _DOWN for pull-down. _NOPULL for floating
	GPIO_Init(port, &GPIO_InitStruct);
}


//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//set systemcoreclock to default hsi
//can only run at 8Mhz
void SystemCoreClockHSI(void) {
	RCC_DeInit();										//reset rcc
	RCC_HSICmd(ENABLE);									//enable hsi
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET) continue;	//wait for hsi to be ready
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);				//set hsi as sysclk
	
	SystemCoreClockUpdate();							//update system core clock
}

//set systemcoreclock to 8Mhz / 2 * RCC_PLLMul_x (x=[2..16])
//Need to check wait state
void SystemCoreClockHSIPLL(uint32_t RCC_PLLMul_x) {
	RCC_DeInit();										//reset rcc
	RCC_PLLCmd(DISABLE);								//disable PLL
	RCC_HSICmd(ENABLE);									//enable hsi;
	RCC_HCLKConfig(RCC_SYSCLK_Div1);					//set sysclk divider
	//RCC_PCLK1Config(RCC_HCLK_Div1);						//set pclk1/2 dividers
	//RCC_PCLK2Config(RCC_HCLK_Div1);
	/**

	* @brief  Configures the PLL clock source and multiplication factor.
	* @note   This function must be used only when the PLL is disabled.
	*
	* @param  RCC_PLLSource: specifies the PLL entry clock source.
	*          This parameter can be one of the following values:
	*            @arg RCC_PLLSource_HSI_Div2: HSI oscillator clock selected as PLL clock source
	*            @arg RCC_PLLSource_PREDIV1: PREDIV1 clock selected as PLL clock entry
	*            @arg RCC_PLLSource_HSI48 HSI48 oscillator clock selected as PLL clock source, applicable only for STM32F072 devices
	*            @arg RCC_PLLSource_HSI: HSI clock selected as PLL clock entry, applicable only for STM32F072 devices
	* @note   The minimum input clock frequency for PLL is 2 MHz (when using HSE as
	*         PLL source).
	*
	* @param  RCC_PLLMul: specifies the PLL multiplication factor, which drive the PLLVCO clock
	*          This parameter can be RCC_PLLMul_x where x:[2,16] 
	*
	* @retval None
	*/
	RCC_PLLConfig(RCC_CFGR_PLLSRC_HSI_Div2, RCC_PLLMul_x);	//configure pll / divider. _x=[2..16]
	RCC_PLLCmd(ENABLE);										//enable pll
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) continue;	//wait for pll to be ready
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);				//set pll as sysclk
	while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL/*0x08*/) continue;		//wait for PLL to be ready

	SystemCoreClockUpdate();								//update SystemCoreClock
}

//reset to hse
void SystemCoreClockHSE(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
	RCC_DeInit();											//reset rcc
	/* Enable HSI Clock */
	RCC_HSICmd(ENABLE);
	RCC_HSEConfig(RCC_HSE_OFF);								//turn off HSE

#if 1														//use library to set up hse - 16 bytes bigger than the register version
	RCC_HCLKConfig(RCC_SYSCLK_Div1);						//set sysclk divider
	
	//enable HSE
	RCC_HSEConfig(RCC_HSE_ON);								//use RCC_HSE_Bypass for external clock

	/*!< Wait till HSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	//configure PLL
	//RCC_PREDIV1Config(RCC_PREDIV1_Div1);
	//RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_x);
	//RCC_PLLCmd(ENABLE); 
	//while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	/* Set HSE as sys clock*/
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	
	//disable HSI
	//RCC_HSICmd(DISABLE);

#else														//use registers to set up hse

	/* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
	/* Enable HSE */    
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
	/* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;  
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	{
		HSEStatus = (uint32_t)0x01;
	}
	else
	{
		HSEStatus = (uint32_t)0x00;
	}  

	if (HSEStatus == (uint32_t)0x01)
	{
		/* Enable Prefetch Buffer and set Flash Latency */
		FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
 
		/* HCLK = SYSCLK */
		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
		/* PCLK = HCLK */
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

		/* PLL configuration = HSE * 6 = 48 MHz */
		//RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
		//RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLMULL6);
            
		/* Enable PLL */
		//RCC->CR |= RCC_CR_PLLON;

		/* Wait till PLL is ready */
		//while((RCC->CR & RCC_CR_PLLRDY) == 0)
		//{
		//}

		/* Select HSE(was PLL) as system clock source */
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE/*PLL*/;    

		/* Wait till HSE(was PLL) is used as system clock source */
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_HSE/*PLL*/)
		{
		}
	}
	else
	{ /* If HSE fails to start-up, the application will have wrong clock 
		configuration. User can add here some code to deal with this error */
	} 
#endif
  
  SystemCoreClockUpdate();									//update system core clock
}

//reset to hse + pll
//RCC_PLLMul_x from RCC_PLLMul_2 to RCC_PLLMul_16
void SystemCoreClockHSEPLL(uint32_t RCC_PLLMul_x)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	RCC_DeInit();											//reset rcc
#if 1														//use rcc library to set up hsepll. About 100 bytes bigger than the library version
	RCC_PLLCmd(DISABLE);									//disable PLL
	
	/* Enable HSE Clock */
	//RCC_HSICmd(ENABLE);
	RCC_HSEConfig(RCC_HSE_ON);								//use RCC_HSE_Bypass for external clock
	RCC_HCLKConfig(RCC_SYSCLK_Div1);						//set sysclk divider

	/*!< Wait till HSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

	//configure PLL
	RCC_PREDIV1Config(RCC_PREDIV1_Div1);
	RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_x);
	RCC_PLLCmd(ENABLE); 
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

	/* Set PLL as sys clock*/
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

#else														//use registers to set up hsepll, from system_stm32f0xx.c
  
  /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

    /* PLL configuration = HSE * 6 = 48 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_PLLMul_x);
            
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }  
#endif
  
	SystemCoreClockUpdate();								//update system core clock
}

//reset the mcu
void mcu_init(void) {
	//RCC_DeInit();											//reset rcc domain
	
	//Use one of the four four options
	//1. HSI
	SystemCoreClockHSI();									//default - keep it here. size=3748-3476 = 270 bytes
	
	//2. HSIPLL
	//FLASH_SetLatency(FLASH_Latency_1);					//needed for over 24Mhz
	//SystemCoreClockHSIPLL_12Mhz();						//speed max out at 48Mhz. size=3976 - 3476 = 500 bytes
	
	//3. HSE
	//SystemCoreClockHSE();									//need capacitors on the crystal / fingers to get the oscillator started. size=3900-3476 = 420 bytes
	
	//4. HSEPLL
	//SystemCoreClockHSEPLL(RCC_PLLMul_2);					//need capacitors on the crystal / fingers to get the oscillator started. size=3980-3476 = 500 bytes
	
	//update SystemCoreClock
	//SystemCoreClockUpdate();								//update SystemCoreClock / F_CPU

	//enable power to gpiox
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);		//for button user
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);	//for leds
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);	//8 bytes each
	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
}

