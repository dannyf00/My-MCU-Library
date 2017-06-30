#include "uart.h"						//we use uart

//initialize UART: 8-bit data, 1 stop bit, no parity
//don't call this routine directly: use uartn_init() instead, where n=0..7
void uart_init(uint32_t uart_base, uint32_t bps) {
	//if (uart >= UARTMAX) return;							//invalid uart number
	switch (uart_base) {
	case UART0_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) continue;	//wait for it to be ready
		GPIOPinConfigure(U0RX_PIN); GPIOPinTypeUART(U0RX_GPIO, U0RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U0TX_PIN); GPIOPinTypeUART(U0TX_GPIO, U0TX_MASK);				//configure the tx pin
		break;
	case UART1_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1)) continue;	//wait for it to be ready
		GPIOPinConfigure(U1RX_PIN); GPIOPinTypeUART(U1RX_GPIO, U1RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U1TX_PIN); GPIOPinTypeUART(U1TX_GPIO, U1TX_MASK);				//configure the tx pin
		break;
	case UART2_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)) continue;	//wait for it to be ready
		GPIOPinConfigure(U2RX_PIN); GPIOPinTypeUART(U2RX_GPIO, U2RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U2TX_PIN); GPIOPinTypeUART(U2TX_GPIO, U2TX_MASK);				//configure the tx pin
		break;
	case UART3_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART3)) continue;	//wait for it to be ready
		GPIOPinConfigure(U3RX_PIN); GPIOPinTypeUART(U3RX_GPIO, U3RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U3TX_PIN); GPIOPinTypeUART(U3TX_GPIO, U3TX_MASK);				//configure the tx pin
		break;
	case UART4_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART4)) continue;	//wait for it to be ready
		GPIOPinConfigure(U4RX_PIN); GPIOPinTypeUART(U4RX_GPIO, U4RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U4TX_PIN); GPIOPinTypeUART(U4TX_GPIO, U4TX_MASK);				//configure the tx pin
		break;
	case UART5_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5)) continue;	//wait for it to be ready
		GPIOPinConfigure(U5RX_PIN); GPIOPinTypeUART(U5RX_GPIO, U5RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U5TX_PIN); GPIOPinTypeUART(U5TX_GPIO, U5TX_MASK);				//configure the tx pin
		break;
	case UART6_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART6)) continue;	//wait for it to be ready
		GPIOPinConfigure(U6RX_PIN); GPIOPinTypeUART(U6RX_GPIO, U6RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U6TX_PIN); GPIOPinTypeUART(U6TX_GPIO, U6TX_MASK);				//configure the tx pin
		break;
	default:
	case UART7_BASE:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);		//enable the peripheral
		while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART7)) continue;	//wait for it to be ready
		GPIOPinConfigure(U7RX_PIN); GPIOPinTypeUART(U7RX_GPIO, U7RX_MASK);				//configure the rx pin
		GPIOPinConfigure(U7TX_PIN); GPIOPinTypeUART(U7TX_GPIO, U7TX_MASK);				//configure the tx pin
		break;
	}
    UARTConfigSetExpClk(uart_base, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTEnable(uart_base);										//enable uart
}

//write a string over serial
//don't call this routine directly: use uartn_puts() instead, where n=0..7
void uart_puts(uint32_t uart, char *str) {
	while (*str) UARTCharPut(uart, *str++);
}
