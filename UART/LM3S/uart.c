#include "uart.h"						//we use uart

//initialize uart
//8-bit, one stop bit, no parity
void uart_init(uint32_t UARTn_BASE, uint32_t bps) {
	switch (UARTn_BASE) {
		//PA0/U0RX, PA1/U0TX
		case UART0_BASE: 
			SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); 
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); 
			GPIOPinConfigure(GPIO_PA0_U0RX); GPIOPinConfigure(GPIO_PA1_U0TX);
			GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); 
			UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); 
			UARTEnable(UART0_BASE);
			break;
		//PD2/U1RX, PD3/U1TX
		case UART1_BASE: 
			SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); 
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); 
			GPIOPinConfigure(GPIO_PD2_U1RX); GPIOPinConfigure(GPIO_PD3_U1TX);
			GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3); 
			UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); 
			UARTEnable(UART1_BASE);
			break;
		//add additional uart if available
		//need to identify the pins associated with the uart, however
		//case UART2_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART2); /*add pin config here*/ UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART2_BASE);break;
		//case UART3_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART3); /*add pin config here*/ UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART3_BASE);break;
		//case UART4_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART4); /*add pin config here*/ UARTConfigSetExpClk(UART4_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART4_BASE);break;
		//case UART5_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART5); /*add pin config here*/ UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART5_BASE);break;
		//case UART6_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART6); /*add pin config here*/ UARTConfigSetExpClk(UART6_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART6_BASE);break;
		//case UART7_BASE: SysCtlPeripheralEnable((SYSCTL_PERIPH_UART7); /*add pin config here*/ UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), bps, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); UARTEnable(UART7_BASE);break;
	};
}


//write a string over serial
void uart_puts(uint32_t uart, char *str) {
	while (*str) UARTCharPut(uart, *str++);
}

