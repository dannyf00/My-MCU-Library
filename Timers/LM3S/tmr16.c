#include "tmr16.h"					//tmr in 16bit mode

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//user handlers
void (*tmr0a_isrptr)(void) = empty_handler;
void (*tmr0b_isrptr)(void) = empty_handler;
void (*tmr1a_isrptr)(void) = empty_handler;
void (*tmr1b_isrptr)(void) = empty_handler;
void (*tmr2a_isrptr)(void) = empty_handler;
void (*tmr2b_isrptr)(void) = empty_handler;

//isr tmr0a
void TMR0A_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //execute the user handler
    tmr0a_isrptr();
}

//isr tmr0b
void TMR0B_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

    //execute the user handler
    tmr0b_isrptr();
}

//isr tmr1a
void TMR1A_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    //execute the user handler
    tmr1a_isrptr();
}

//isr tmr1b
void TMR1B_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);

    //execute the user handler
    tmr1b_isrptr();
}

//isr tmr2a
void TMR2A_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    //execute the user handler
    tmr2a_isrptr();
}

//isr tmr0b
void TMR2B_Handler(void)  {
    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);

    //execute the user handler
    tmr2b_isrptr();
}

//initialize tmr0a
void tmr0a_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER0_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER0_BASE, (_tmr_ctl & ~0x00ff) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER0_BASE, TIMER_A, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER0_BASE, TIMER_A, TMR0A_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER0_BASE, TIMER_A);
}

//install a user handler
void tmr0a_act(void (*isrptr)(void)) {
	tmr0a_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

//test timer flag is set
uint32_t tmr0a_ovfset(void) {
	return MAP_TimerIntStatus(TIMER0_BASE, false) & TIMER_TIMA_TIMEOUT;
}

//clear the flag
void tmr0a_ovfclr(void) {
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

//initialize tmr0b
void tmr0b_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER0_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER0_BASE, (_tmr_ctl & ~0xff00) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_B, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER0_BASE, TIMER_B, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER0_BASE, TIMER_B, TMR0B_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER0_BASE, TIMER_B);
}

//install a user handler
void tmr0b_act(void (*isrptr)(void)) {
	tmr0b_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

//test timer flag is set
uint32_t tmr0b_ovfset(void) {
	return MAP_TimerIntStatus(TIMER0_BASE, false) & TIMER_TIMB_TIMEOUT;
}

//clear the flag
void tmr0b_ovfclr(void) {
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}
//initialize tmr1a
void tmr1a_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER1_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER1_BASE, (_tmr_ctl & ~0x00ff) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER1_BASE, TIMER_A, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntDisable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER1_BASE, TIMER_A, TMR1A_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER1_BASE, TIMER_A);
}

//install a user handler
void tmr1a_act(void (*isrptr)(void)) {
	tmr1a_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}

//test timer flag is set
uint32_t tmr1a_ovfset(void) {
	return MAP_TimerIntStatus(TIMER1_BASE, false) & TIMER_TIMA_TIMEOUT;
}

//clear the flag
void tmr1a_ovfclr(void) {
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}

//initialize tmr0b
void tmr1b_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER1_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER1_BASE, (_tmr_ctl & ~0xff00) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_B, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER1_BASE, TIMER_B, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntDisable(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER1_BASE, TIMER_B, TMR1B_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER1_BASE, TIMER_B);
}

//install a user handler
void tmr1b_act(void (*isrptr)(void)) {
	tmr1b_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
}

//test timer flag is set
uint32_t tmr1b_ovfset(void) {
	return MAP_TimerIntStatus(TIMER1_BASE, false) & TIMER_TIMB_TIMEOUT;
}

//clear the flag
void tmr1b_ovfclr(void) {
	MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMB_TIMEOUT);
}
//initialize tmr2a
void tmr2a_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER2_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER2_BASE, (_tmr_ctl & ~0x00ff) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_A, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntDisable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER2_BASE, TIMER_A, TMR2A_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER2_BASE, TIMER_A);
}

//install a user handler
void tmr2a_act(void (*isrptr)(void)) {
	tmr2a_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
	MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}

//test timer flag is set
uint32_t tmr2a_ovfset(void) {
	return MAP_TimerIntStatus(TIMER2_BASE, false) & TIMER_TIMA_TIMEOUT;
}

//clear the flag
void tmr2a_ovfclr(void) {
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}

//initialize tmr2b
void tmr2b_init(uint16_t ps, uint16_t pr) {
	uint32_t _tmr_ctl;
	
	//optional
	//
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    //MAP_FPULazyStackingEnable();

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

	//save the current status of the timer on/off
    //HWREG() used to so that TIMER_A settings are preserved - a Tivaware stupidity
	_tmr_ctl=HWREG(TIMER2_BASE + TIMER_O_CTL);

    //
    // Configure the two 16-bit periodic downcounter timers.
    //
    MAP_TimerConfigure(TIMER2_BASE, (_tmr_ctl & ~0xff00) | TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);			//set timer as periodic downcounter
    //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_B, pr-1);				//set timer period, count down timer so no period - 1
    //MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, MAP_SysCtlClockGet() / 2);
    MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_B, ps-1);				//set prescaler
	
	//clear the flag, and keep the interrupt disabled
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntDisable(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
	
	//register isr
	TimerIntRegister(TIMER2_BASE, TIMER_B, TMR2B_Handler);
	
	//enable the timer
	MAP_TimerEnable(TIMER2_BASE, TIMER_B);
}

//install a user handler
void tmr2b_act(void (*isrptr)(void)) {
	tmr2b_isrptr = isrptr;						//install user handler
	//clear the flag, and enable the interrupt
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
	MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
}

//test timer flag is set
uint32_t tmr2b_ovfset(void) {
	return MAP_TimerIntStatus(TIMER2_BASE, false) & TIMER_TIMB_TIMEOUT;
}

//clear the flag
void tmr2b_ovfclr(void) {
	MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMB_TIMEOUT);
}
