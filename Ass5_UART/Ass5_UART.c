#include "MKE16Z4.h"

#define SystemCoreClock		48000000
#define BaudRate_UART		9600

void initUART0() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1); /* Configure clock for PORT B */
	PORTA->PCR[0] |= PORT_PCR_MUX(2); /* 0b010 << 8 */
	PORTA->PCR[1] |= PORT_PCR_MUX(2); /* 0b010 << 8 */

	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3); /* 0b011 << 24 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_CGC(1); /* 1 << 30 */
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1); /* 1 << 8 */

	LPUART0->CTRL &= ~(1 << 19 | 1 << 18); /* Disable TE & RE while configuring*/

	LPUART0->CTRL &= ~(1 << 4); /* 8-bit mode select */

//	LPUART0->CTRL |= 1 << 23; /* Configure TIE */
//	LPUART0->CTRL |= 1 << 22; /* Configure TCIE */
//	LPUART0->CTRL |= 1 << 21; /* Configure RIE */

	LPUART0->STAT &= ~(1 << 29); /* Set LSB for data transmission ->> bit start = 0 */

	LPUART0->BAUD |= 1 << 17; /* Set BOTHEDGE */
	LPUART0->BAUD &= ~(0b1011 << 24); /* Set OSR = 4 -> OSR + 1 = 5 */
	LPUART0->BAUD |= LPUART_BAUD_SBR(1000); /* OSR = 0b0100 -> OSR + 1 = 5 */

	LPUART0->BAUD &= ~(1 << 13); /* Configure for 1 stop bit */

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
