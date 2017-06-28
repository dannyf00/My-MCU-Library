#ifndef _UART_H
#define _UART_H

/*	demo to use uart hardware
 */

//baud rate definitions
#define F_UART				(F_CPU)	//8Mhz		//crystal frequency
#define UART_BR_300		300ul		//buadrate=300
#define UART_BR_600		600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

#define uart_put(n)		uart_putch(n)
#define uart_get()		uart_getch()
#define uart_available()	(UCSR0A & (1<<RXC0))
#define uart_busy()		(UCSR0A & (1<<UDRE0))

void uart_init(unsigned long baud);

void uart_putch(unsigned char data_t);			//send data

void uart_puts(unsigned char * str);			//put a string

void uart_putline(unsigned char * str);			//put a string, with line return

unsigned char uart_getch(void);					//get a char from uart

#endif
