#include "tim8oc.h"					//using timer output compare channels as timer

//hardware configuration
//end hardware configuration

//global defines
#define RCC_TIMxEN						RCC_APB2ENR_TIM8EN
#define TIMx							TIM8
#define TIMx_CC_IRQn					TIM8_CC_IRQn

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variables
static void (* _tim_oc1isrptr)(void)=empty_handler;				//tim8_ptr pointing to empty_handler by default
static void (* _tim_oc2isrptr)(void)=empty_handler;				//tim8_ptr pointing to empty_handler by default
static void (* _tim_oc3isrptr)(void)=empty_handler;				//tim8_ptr pointing to empty_handler by default
static void (* _tim_oc4isrptr)(void)=empty_handler;				//tim8_ptr pointing to empty_handler by default

static uint32_t _tim_oc1=0;				//output compare registers
static uint32_t _tim_oc2=0;
static uint32_t _tim_oc3=0;
static uint32_t _tim_oc4=0;

//isr for timer3 capture / compare
void TIM8_IRQHandler(void) {
	//oc1 portion
	if (TIMx->SR & TIM_SR_CC1IF) {		//output compare 1 flag is set
		TIMx->SR &=~TIM_SR_CC1IF;		//clear the flag
		TIMx->CCR1 += _tim_oc1;			//update the output compare register
		_tim_oc1isrptr();				//execute user handler
	}

	//oc2 portion
	if (TIMx->SR & TIM_SR_CC2IF) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC2IF;		//clear the flag
		TIMx->CCR2 += _tim_oc2;			//update the output compare register
		_tim_oc2isrptr();				//execute user handler
	}

	//oc3 portion
	if (TIMx->SR & TIM_SR_CC3IF) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC3IF;		//clear the flag
		TIMx->CCR3 += _tim_oc3;			//update the output compare register
		_tim_oc3isrptr();				//execute user handler
	}

	//oc4 portion
	if (TIMx->SR & TIM_SR_CC4IF) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC4IF;		//clear the flag
		TIMx->CCR4 += _tim_oc4;			//update the output compare register
		_tim_oc4isrptr();				//execute user handler
	}
}

//initialize tim8 to use compare channels as timers
//16-bit prescaler. 32-bit used for compatibility
void tim8_init(uint32_t ps) {
	//route the clock to timer
	RCC->APB2ENR |= RCC_TIMxEN;

	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	TIMx->CR1 &=~TIM_CR1_ARPE;			//1=arr is buffered, 0=arr not buffered
	//or to simply zero the register
	//TIMx->CR1 = 0;						//much easier

	//clear the status register bits for capture / compare flags
	TIMx->SR &=~(TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF | TIM_SR_CC4IF);
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~(TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE);

	//set the prescaler
	TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter

	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//set tim8_oc1 period
//pr is 16-bit. 32-bit used for compatability;
void tim8_setpr1(uint32_t pr) {
	//save the period value
	_tim_oc1 = pr - 1;
	TIMx->CCR1 = TIMx->CNT + _tim_oc1;

	//clear the flag
	//TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	//TIMx->DIER &=~TIM_DIER_CC1IE;		//disable the isr
}

//install user handler
void tim8_act1(void (*isr_ptr)(void)) {
	NVIC_DisableIRQ(TIMx_CC_IRQn);		//disable irq

	_tim_oc1isrptr = isr_ptr;			//install user handler

	//clear the flag
	TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	TIMx->DIER |= TIM_DIER_CC1IE;		//enable the isr

	NVIC_EnableIRQ(TIMx_CC_IRQn);		//enable irq
	//priorities not set -> default values used.

	TIMx->EGR |= TIM_EGR_UG;			//force an update
}

//set tim8_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim8_setpr2(uint32_t pr) {
	//save the period value
	_tim_oc2 = pr - 1;
	TIMx->CCR2 = TIMx->CNT + _tim_oc2;

	//clear the flag
	//TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	//TIMx->DIER &=~TIM_DIER_CC1IE;		//disable the isr
}

//install user handler
void tim8_act2(void (*isr_ptr)(void)) {
	NVIC_DisableIRQ(TIMx_CC_IRQn);		//disable irq

	_tim_oc2isrptr = isr_ptr;			//install user handler

	//clear the flag
	TIMx->SR &=~TIM_SR_CC2IF;			//clear the interrupt flag
	TIMx->DIER |= TIM_DIER_CC2IE;		//enable the isr

	NVIC_EnableIRQ(TIMx_CC_IRQn);		//enable irq
	//priorities not set -> default values used.

	TIMx->EGR |= TIM_EGR_UG;			//force an update

}

//set tim8_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim8_setpr3(uint32_t pr) {
	//save the period value
	_tim_oc3 = pr - 1;
	TIMx->CCR3 = TIMx->CNT + _tim_oc3;

	//clear the flag
	//TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	//TIMx->DIER &=~TIM_DIER_CC1IE;		//disable the isr
}

//install user handler
void tim8_act3(void (*isr_ptr)(void)) {
	NVIC_DisableIRQ(TIMx_CC_IRQn);		//disable irq

	_tim_oc3isrptr = isr_ptr;			//install user handler

	//clear the flag
	TIMx->SR &=~TIM_SR_CC3IF;			//clear the interrupt flag
	TIMx->DIER |= TIM_DIER_CC3IE;		//enable the isr

	NVIC_EnableIRQ(TIMx_CC_IRQn);		//enable irq
	//priorities not set -> default values used.

	TIMx->EGR |= TIM_EGR_UG;			//force an update

}

//set tim8_oc2 period
//pr is 16-bit. 32-bit used for compatability;
void tim8_setpr4(uint32_t pr) {
	//save the period value
	_tim_oc4 = pr - 1;
	TIMx->CCR4 = TIMx->CNT + _tim_oc4;

	//clear the flag
	//TIMx->SR &=~TIM_SR_CC1IF;			//clear the interrupt flag
	//TIMx->DIER &=~TIM_DIER_CC1IE;		//disable the isr
}

//install user handler
void tim8_act4(void (*isr_ptr)(void)) {
	NVIC_DisableIRQ(TIMx_CC_IRQn);		//disable irq

	_tim_oc4isrptr = isr_ptr;			//install user handler

	//clear the flag
	TIMx->SR &=~TIM_SR_CC4IF;			//clear the interrupt flag
	TIMx->DIER |= TIM_DIER_CC4IE;		//enable the isr

	NVIC_EnableIRQ(TIMx_CC_IRQn);		//enable irq
	//priorities not set -> default values used.

	TIMx->EGR |= TIM_EGR_UG;			//force an update

}
