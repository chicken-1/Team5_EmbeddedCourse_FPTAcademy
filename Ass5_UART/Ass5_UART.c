#include "MKE16Z4.h"

#define SystemCoreClock		48000000
#define BaudRate_UART		9600

void initUART0() {
	PCC->CLKCFG[PCC_PORTA_INDEX] |= PCC_CLKCFG_CGC(1); /* Configure clock for PORT A */
	PORTA->PCR[3] |= PORT_PCR_MUX(4); /* 0b100 << 8 */

	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3); /* 0b011 << 24 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_CGC(1); /* 1 << 30 */
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1); /* 1 << 8 */

	LPUART0->CTRL &= ~(1 << 19 | 1 << 18); /* Disable TE & RE while configuring*/
	LPUART0->CTRL &= ~(1 << 4); /* 8-bit mode select */
	LPUART0->CTRL |= 1 << 23; /* Configure TIE */
	LPUART0->CTRL |= 1 << 22; /* Configure TCIE */
	LPUART0->CTRL |= 1 << 21; /* Configure RIE */

	LPUART0->STAT &= ~(1 << 29); /* Set LSB for data transmission ->> bit start = 0 */

//	LPUART0->DATA |= 1 << 8; /* Read receive data buffer 8 or write transmit data buffer 8 */

	LPUART0->BAUD = (SystemCoreClock / (BaudRate_UART * 16)); /* OSR = 0b1111 -> OSR + 1 = 16 */

	LPUART0->BAUD |= 1 << 13; /* Configure for 1 stop bit */

	LPUART0->CTRL |= (1 << 19 | 1 << 18); /* Enable TE & RE */
}

void UART0_SendChar(uint8_t data) {
	while(!(LPUART0->STAT & LPUART_STAT_TDRE_MASK)) {}
	LPUART0->DATA = data;
}

void UART0_SendString(uint8_t *str) {
	while(*str != '\0') {
		UART0_SendChar(*str++);
	}
}

int main () {
//	uint8_t string = 'Hello World';

	initUART0();
	UART0_SendString((uint8_t *)"Hello World");
}
