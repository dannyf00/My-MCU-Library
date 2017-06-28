#ifndef UART_H
#define UART_H

#include "gpio.h"

//bps macros - optional
#define UART_BPS2400			2400
#define UART_BPS4800			4800
#define UART_BPS9600			9600
#define UARB_BPS19200			19200
#define UART_BPS38400			38400
//end bps macros

//for uart0
#define uart0_init(bps)			uart_init(UART0_BASE, bps)
#define uart0_putc(ch)			uart_putc(UART0_BASE, ch)
#define uart0_puts(str)			uart_puts(UART0_BASE, str)
#define uart0_getc()			uart_getc(UART0_BASE)
#define uart0_busy()			UARTBusy(UART0_BASE)
#define uart0_available()		UARTCharAvailable(UART0_BASE)

//for uart1
#define uart1_init(bps)			uart_init(UART1_BASE, bps)
#define uart1_putc(ch)			uart_putc(UART1_BASE, ch)
#define uart1_puts(str)			uart_puts(UART1_BASE, str)
#define uart1_getc()			uart_getc(UART1_BASE)
#define uart1_busy()			UARTBusy(UART1_BASE)
#define uart1_available()		UARTCharAvailable(UART1_BASE)

//generic macros
#define uart_putc(uart, ch)		UARTCharPut(uart, ch)
#define uart_getc(uart)			UARTCharGet(uart)

//initialize uart
void uart_init(uint32_t UARTn_BASE, uint32_t bps);
//write a string over serial
void uart_puts(uint32_t UARTn_BASE, char *str);


#endif
