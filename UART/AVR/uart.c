/*	demo to use uart hardware
 */

#include <iccioavr.h>
#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "uart_hw.h"

//baud rate definitions
#define USART_BR_300		300ul
#define USART_BR_1200		1200ul
#define USART_BR_2400		2400ul
#define USART_BR_4800		4800ul
#define USART_BR_9600		9600ul
#define USART_BR_14400		14400ul
#define USART_BR_19200		19200ul
#define USART_BR_38400		38400ul
#define USART_BR_57600		57600ul

#define USART_FOSC			1000000ul			//cpu speed

void uart_init(unsigned long baud) {

	/* baud rate generator */
	//UBRR0H=(unsigned char) (baud >> 8);
	//UBRR0L=(unsigned char) baud;
	UBRR=USART_FOSC / 16 / baud - 1;			//generate baud rate register

	/* enable receiver and transmitter */
	UCSRB=		(0<<RXCIE) |					//disable RX complete interrupt
				(0<<TXCIE) |					//disable TX complete interrupt
				(0<<UDRIE) |					//disable usart data register empty interrupt
				(1<<RXEN) |						//enable receiver
				(1<<TXEN) |						//enable transmitter
				(0<<UCSZ2) |					//char size
				(0<<RXB8) |						//receive data bit 8 / 9th data bit received
				(0<<TXB8);						//transmitter data bit 8 / 9th data bit to be sent

	/* set frame format: 8 data, 1 stop bit */
	UCSRC=		(0<<UMSEL1) | (0<<UMSEL0) |		//00-> asynchronous usart
												//01-> synchronous usart
												//10-> reserved
												//11-> master spi
				(0<<UPM1) | (0<<UPM0) |			//parity check 00-> disabled
												//01-> reserved
												//10-> enabled, even parity
												//11-> enabled, odd parity
				(0<<USBS) |						//stop bit select. 0->1 bit, 1->2bit
				(1<<UCSZ1) | (1<<UCSZ0) |		//char size.
												//000-> 5-bit
												//001-> 6-bit
												//010-> 7-bit
												//011-> 8-bit
												//100-> reserved
												//101-> reserved
												//110-> reserved
												//111-> 9-bit
				(0<<UCPOL);						//clock polarity. 0-> rising xck edge. 1-> falling xck edge
	//DDRD |= (1<<5);							//xck as output

}

void uart_putch(unsigned char data_t) {			//send data
	UDR=data_t;									//load up the buffer
	while (!(UCSRA & (1<<UDRE)));				//wait for transmission to end
	//return 0;									//transmission complete
}

void uart_puts(unsigned char * str) {			//put a string
	while (*str)								//if the string isn't empty
		uart_putch(*str++);						//send the char and advance the pointer
}

void uart_putline(unsigned char * str) {
	uart_puts(str);
	uart_puts("\r\n");
}

unsigned char uart_getch(void) {
	while (!(UCSRA & (1<<RXC))) continue;		//wait for the receive to finish
	return UDR;									//return the context of uart register
}
