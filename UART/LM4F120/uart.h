#ifndef UART_H_
#define UART_H_

#include "gpio.h"						//we use gpio

//for LM4F120/TM4C1233H6PM
//for UART0
#define U0RX_GPIO			GPIOA
#define U0RX_MASK			(1<<0)
#define U0RX_PIN			GPIO_PA0_U0RX
#define U0TX_GPIO			GPIOA
#define U0TX_MASK			(1<<1)
#define U0TX_PIN			GPIO_PA1_U0TX

//for UART1
#define U1RX_GPIO			GPIOB
#define U1RX_MASK			(1<<0)
#define U1RX_PIN			GPIO_PB0_U1RX
#define U1TX_GPIO			GPIOB
#define U1TX_MASK			(1<<1)
#define U1TX_PIN			GPIO_PB1_U1TX

//for UART2
#define U2RX_GPIO			GPIOD
#define U2RX_MASK			(1<<6)
#define U2RX_PIN			GPIO_PD6_U2RX
#define U2TX_GPIO			GPIOD
#define U2TX_MASK			(1<<7)
#define U2TX_PIN			GPIO_PD7_U2TX

//for UART3
#define U3RX_GPIO			GPIOC
#define U3RX_MASK			(1<<6)
#define U3RX_PIN			GPIO_PC6_U3RX
#define U3TX_GPIO			GPIOC
#define U3TX_MASK			(1<<7)
#define U3TX_PIN			GPIO_PC7_U3TX

//for UART4
#define U4RX_GPIO			GPIOC
#define U4RX_MASK			(1<<4)
#define U4RX_PIN			GPIO_PC4_U4RX
#define U4TX_GPIO			GPIOC
#define U4TX_MASK			(1<<5)
#define U4TX_PIN			GPIO_PC5_U4TX

//for UART5
#define U5RX_GPIO			GPIOE
#define U5RX_MASK			(1<<4)
#define U5RX_PIN			GPIO_PE4_U5RX
#define U5TX_GPIO			GPIOE
#define U5TX_MASK			(1<<5)
#define U5TX_PIN			GPIO_PE5_U5TX

//for UART6
#define U6RX_GPIO			GPIOD
#define U6RX_MASK			(1<<4)
#define U6RX_PIN			GPIO_PD4_U6RX
#define U6TX_GPIO			GPIOD
#define U6TX_MASK			(1<<5)
#define U6TX_PIN			GPIO_PD5_U6TX

//for UART7
#define U7RX_GPIO			GPIOE
#define U7RX_MASK			(1<<0)
#define U7RX_PIN			GPIO_PE0_U7RX
#define U7TX_GPIO			GPIOE
#define U7TX_MASK			(1<<1)
#define U7TX_PIN			GPIO_PE1_U7TX

//initialize the uart
#define uart0_init(bps)		uart_init(UART0_BASE, bps)
#define uart1_init(bps)		uart_init(UART1_BASE, bps)
#define uart2_init(bps)		uart_init(UART2_BASE, bps)
#define uart3_init(bps)		uart_init(UART3_BASE, bps)
#define uart4_init(bps)		uart_init(UART4_BASE, bps)
#define uart5_init(bps)		uart_init(UART5_BASE, bps)
#define uart6_init(bps)		uart_init(UART6_BASE, bps)
#define uart7_init(bps)		uart_init(UART7_BASE, bps)

//send a char
#define uart0_put(ch)		UARTCharPut(UART0_BASE, ch)
#define uart1_put(ch)		UARTCharPut(UART1_BASE, ch)
#define uart2_put(ch)		UARTCharPut(UART2_BASE, ch)
#define uart3_put(ch)		UARTCharPut(UART3_BASE, ch)
#define uart4_put(ch)		UARTCharPut(UART4_BASE, ch)
#define uart5_put(ch)		UARTCharPut(UART5_BASE, ch)
#define uart6_put(ch)		UARTCharPut(UART6_BASE, ch)
#define uart7_put(ch)		UARTCharPut(UART7_BASE, ch)

//send a string
#define uart0_puts(str)		uart_puts(UART0_BASE, str)
#define uart1_puts(str)		uart_puts(UART1_BASE, str)
#define uart2_puts(str)		uart_puts(UART2_BASE, str)
#define uart3_puts(str)		uart_puts(UART3_BASE, str)
#define uart4_puts(str)		uart_puts(UART4_BASE, str)
#define uart5_puts(str)		uart_puts(UART5_BASE, str)
#define uart6_puts(str)		uart_puts(UART6_BASE, str)
#define uart7_puts(str)		uart_puts(UART7_BASE, str)

//test if data is available from the receiver
#define uart0_available()	UARTCharsAvail(UART0_BASE)
#define uart1_available()	UARTCharsAvail(UART1_BASE)
#define uart2_available()	UARTCharsAvail(UART2_BASE)
#define uart3_available()	UARTCharsAvail(UART3_BASE)
#define uart4_available()	UARTCharsAvail(UART4_BASE)
#define uart5_available()	UARTCharsAvail(UART5_BASE)
#define uart6_available()	UARTCharsAvail(UART6_BASE)
#define uart7_available()	UARTCharsAvail(UART7_BASE)

//test if uart transmitter is busy
#define uart0_busy()		UARTBusy(UART0_BASE)
#define uart1_busy()		UARTBusy(UART1_BASE)
#define uart2_busy()		UARTBusy(UART2_BASE)
#define uart3_busy()		UARTBusy(UART3_BASE)
#define uart4_busy()		UARTBusy(UART4_BASE)
#define uart5_busy()		UARTBusy(UART5_BASE)
#define uart6_busy()		UARTBusy(UART6_BASE)
#define uart7_busy()		UARTBusy(UART7_BASE)

//retrive data from the receiver
#define uart0_get()			UARTCharGet(UART0_BASE)
#define uart1_get()			UARTCharGet(UART1_BASE)
#define uart2_get()			UARTCharGet(UART2_BASE)
#define uart3_get()			UARTCharGet(UART3_BASE)
#define uart4_get()			UARTCharGet(UART4_BASE)
#define uart5_get()			UARTCharGet(UART5_BASE)
#define uart6_get()			UARTCharGet(UART6_BASE)
#define uart7_get()			UARTCharGet(UART7_BASE)

//initialize UART: 8-bit data, 1 stop bit, no parity
void uart_init(uint32_t uart_base, uint32_t bps);
void uart_puts(uint32_t uart_base, char *str);

#endif /* UART_H_ */
