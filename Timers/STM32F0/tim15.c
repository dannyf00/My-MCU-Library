//#include <stm32f4xx.h>
//#include "gpio.h"						//we use own macros
//#include "delay.h"					//we use software delay
#include "tim15.h"						//we use hardware timer

//empty handler
static void /*_tmr6_*/empty_handler(void) {
	//default tmr handler
}

//global defines
#define TIMx		TIM15
#define RCC_TIMx	RCC_APB2Periph_TIM15


//global variables
static void (* /*_tmr*/_isr_ptr)(void)=empty_handler;	//tmr1_ptr pointing to empty_handler by default

//initialize the timer
//timer set to
void tmr15_init(uint16_t ps, uint16_t period) {
	TIM_TimeBaseInitTypeDef tmr;

	//set clock to TIM3
	RCC_APB2PeriphClockCmd(RCC_TIMx, ENABLE);

	//timer basestructure 24mhz/(0+1)/(0+1) ~ 2,72mS (655353/24000000)s for full period
	tmr.TIM_Prescaler = ps-1 ;
	tmr.TIM_CounterMode = TIM_CounterMode_Up;			//can be TIM_CounterMode_Up or TIM_CounterMode_Down
	tmr.TIM_Period = period-1;							//set the period
	tmr.TIM_ClockDivision = TIM_CKD_DIV1;
	tmr.TIM_RepetitionCounter = /*period-1*/0;			//counter runs in repetition
	TIM_TimeBaseInit(TIMx, &tmr);						//initialize the timer

	/* TIM IT enable */
	//TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

	//reset isr ptr
	/*_tmr*/_isr_ptr = /*_tmr6_*/empty_handler;

	//enable the timer
	TIM_Cmd(TIMx, ENABLE);
}

//install user handler
void tmr15_act(void (*isr_ptr)(void)) {
	NVIC_InitTypeDef NVIC_InitStructure;

	/* TIM IT enable */
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

	//enable tim4 irq
	NVIC_InitStructure.NVIC_IRQChannel = TIM15_IRQn;	//tim4 irq
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//0-15
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;		//0-15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);						//enable timer irq

	/*_tmr*/_isr_ptr = isr_ptr;

}

//timer 6 interrupt
void TIM15_IRQHandler(void){

	//if interrupt happens the do this
	//if(TIM_GetITStatus(TIMx, TIM_IT_Update) != RESET){
	if (TIMx->SR & TIM_IT_Update) {
		//clear interrupt and start counting again to get precise freq
		/* Clear the IT pending Bit */
		TIMx->SR = (uint16_t)~TIM_IT_Update;			//for speed reasons. bit is rc_w0
		/*_tmr*/_isr_ptr();								//IO_FLP(LED_PORT, LED2);
	}
}

