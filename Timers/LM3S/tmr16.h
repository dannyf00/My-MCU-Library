#ifndef _TMR16_H
#define _TMR16_H

//header file for timers in 16-bit mode

#include "gpio.h"						//we use gpio


//initialize tmr

//for tmr0
void tmr0a_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr0a_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr0a_ovfset(void);
//clear the flag
void tmr0a_ovfclr(void);

void tmr0b_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr0b_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr0b_ovfset(void);
//clear the flag
void tmr0b_ovfclr(void);
//end of tmr0

//for tmr1
void tmr1a_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr1a_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr1a_ovfset(void);
//clear the flag
void tmr1a_ovfclr(void);

void tmr1b_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr1b_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr1b_ovfset(void);
//clear the flag
void tmr1b_ovfclr(void);
//end of tmr1

//for tmr2
void tmr2a_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr2a_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr2a_ovfset(void);
//clear the flag
void tmr2a_ovfclr(void);

void tmr2b_init(uint16_t ps, uint16_t pr);
//install a user handler
void tmr2b_act(void (*isrptr)(void));
//test timer flag is set
uint32_t tmr2b_ovfset(void);
//clear the flag
void tmr2b_ovfclr(void);
//end of tmr2
#endif
