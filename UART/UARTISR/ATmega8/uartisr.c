/*	demo to use uart hardware
 */

//#include <iccioavr.h>
//#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "uart.h"

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

//for compatability
#define UxBRR				UBRR
#define UxCSRA				UCSRA
#define UxCSRB				UCSRB
#define UxCSRC				UCSRC
#define UxDR				UDR

//global variables
static volatile uint8_t	_UxTX_BUSY = 0;			//1->UxTX is busy
static char *_UxTX_ptr;							//point to string to be transmitted

//UxTX isr
//usi ovf interrupt
ISR(USART_TXC_vect) {
	//USISR |= (1<<USIOIF);							//clear the flag by writing 1 to it
	//*_USI_ptr = USIDR;								//save the returned data
	if (*_UxTX_ptr) {							//last non-zero char has been sent
		UxDR = *_UxTX_ptr++;						//load the data into transmitter
	} else {
		_UxTX_BUSY = 0;							//no long busy
		UxCSRA &=~(1<<TXCIE);					//disable the interrupt
	}
}

//uart for 8-bit, 1stop bit, no parity transmission
void uart_init(unsigned long baud) {

	//check to see if if rx/tx pins are defined
#if defined(UxTX)								//TX as output
	IO_OUT(UxDDR, UxTX);
#endif

#if defined(UxRX)								//RX as input
	IO_IN(UxDDR, UxRX);
#endif

	/* enable receiver and transmitter */
	UxCSRA=		(1<<U2X);						//double speed
	UxCSRB=		(0<<RXCIE) |					//0->disable RX complete interrupt
				(0<<TXCIE) |					//0->disable TX complete interrupt
				(0<<UDRIE) |					//0->disable usart data register empty interrupt
#if defined(UxRX)
				(1<<RXEN) |					//1->enable receiver
#else
				(0<<RXEN) |					//1->enable receiver
#endif
#if defined(UxTX)
				(1<<TXEN) |					//1->enable transmitter
#else
				(0<<TXEN) |					//1->enable transmitter
#endif
				(0<<UCSZ2) |					//char size 0b011->8bit
				(0<<RXB8) |					//receive data bit 8 / 9th data bit received
				(0<<TXB8);						//transmitter data bit 8 / 9th data bit to be sent

	/* set frame format: 8 data, 1 stop bit */
	UxCSRC=		(1<<URSEL) |				//'1'->access as UxCSRC. '0'->access as BRRH
				//(0<<UMSEL1) |
				(0<<UMSEL) |					//0-> asynchronous usart
												//01-> synchronous usart
												//10-> reserved
												//11-> master spi
				(0<<UPM1) | (0<<UPM0) |		//parity check 00-> disabled
												//01-> reserved
												//10-> enabled, even parity
												//11-> enabled, odd parity
				(0<<USBS) |					//stop bit select. 0->1 bit, 1->2bit
				(1<<UCSZ1) | (1<<UCSZ0) |		//char size.
												//000-> 5-bit
												//001-> 6-bit
												//010-> 7-bit
												//011-> 8-bit
												//100-> reserved
												//101-> reserved
												//110-> reserved
												//111-> 9-bit
				(1<<UCPOL);					//clock polarity. 0-> rising xck edge. 1-> falling xck edge
	/* baud rate generator */
	//UBRR0H=(unsigned char) (baud >> 8);
	//UBRR0L=(unsigned char) baud;
	uint16_t BRR=F_UART / ((UxCSRA & (1<<U2X))?8:16) / baud - 1;			//generate baud rate register
	UBRRH = BRR >> 8;
	UBRRL = BRR;

	//DDRD |= (1<<5);							//xck as output

}

void uart_putch(char data_t) {					//send data
	while (!(UxCSRA & (1<<UDRE)));				//wait for transmission to end
	UxDR=data_t;								//load up the buffer
	//return 0;									//transmission complete
}

void uart_puts(char * str) {					//put a string
	//while (*str)								//if the string isn't empty
	//	uart_putch(*str++);						//send the char and advance the pointer
	if (*str) {
		_UxTX_BUSY = 1;							//1->UxTX is busy
		_UxTX_ptr = str;						//point to string to be transmitted
		UxDR = *_UxTX_ptr++;					//load up the string and advance to the next char
		UxCSRB|= (1<<TXCIE);					//enable interrupt
	}
}

void uart_putline(char * str) {
	uart_puts(str);
	uart_puts("\r\n");
}

char uart_getch(void) {
	//while (!(UxCSRA & (1<<RXC0))) continue;		//wait for the receive to finish
	return UxDR;									//return the context of uart register
}

//test if uart receiver has data
uint8_t uart_available(void) {
	return UxCSRA & (1<<RXC);					//RXC0 set if data is available
}

//test if transmitter is busy
uint8_t uart_busy(void) {
	return _UxTX_BUSY;							//!(UxCSRA & (1<<UDRE0));			//UDRE0 set if tx buffer is empty
	//return !(UxCSRA & (1<<UDRE0));			//UDRE0 set if tx buffer is empty
}
