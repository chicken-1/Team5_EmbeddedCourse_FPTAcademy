#include "MKE16Z4.h"
#include <string.h>

#define SystemCoreClock		48000000
#define BaudRate_UART		9600

uint8_t data_receive[50];
uint8_t comp_flag = 0;
uint8_t string_task[14] = 	"Hello from PC!";
uint8_t count = 0;

void Delay()
{
	uint32_t index;
	for(index = 0; index < 3750000; index++){
		__asm("nop");
	}
}

void initUART0() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1); /* Configure clock for PORT B */
	PORTB->PCR[0] |= PORT_PCR_MUX(2); /* 0b010 << 8 */
	PORTB->PCR[1] |= PORT_PCR_MUX(2); /* 0b010 << 8 */

	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3); /* 0b011 << 24 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_CGC(1); /* 1 << 30 */
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1); /* 1 << 8 */

	//LPUART0->CTRL &= ~(1 << 19 | 1 << 18); /* Disable TE & RE while configuring*/

	LPUART0->CTRL &= ~(1 << 4); /* 8-bit mode select */

//	LPUART0->CTRL |= 1 << 23; /* Configure TIE */
//	LPUART0->CTRL |= 1 << 22; /* Configure TCIE */
//	LPUART0->CTRL |= 1 << 21; /* Configure RIE */

	LPUART0->STAT &= ~(1 << 29); /* Set LSB for data transmission ->> bit start = 0 */

	LPUART0->BAUD |= 1 << 17; /* Set BOTHEDGE */
	LPUART0->BAUD &= ~(0b1011 << 24); /* Set OSR = 4 -> OSR + 1 = 5 */
	LPUART0->BAUD |= LPUART_BAUD_SBR(1000); /* OSR = 0b0100 -> OSR + 1 = 5 */

	LPUART0->BAUD &= ~(1 << 13); /* Configure for 1 stop bit */

	LPUART0->CTRL |= 1 << 21; /* Enable receive interrupt */

	__NVIC_EnableIRQ(LPUART0_IRQn);	/* Enable NVIC */

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

void LPUART0_IRQHandler() {
	uint8_t data = 0;
	if(count == 14){
			count = 0;
		}
	data = LPUART0->DATA & 0xFF;

	if(data != string_task[count]){
		//UART0_SendChar(data);
		comp_flag = 1;
	}
	count ++;
	if(comp_flag == 0 && count == 14){
				UART0_SendString((uint8_t *)"Hello World\n");
	}if(comp_flag == 1){
				comp_flag = 0;
				count = 0;
	}

}
int main () {

	initUART0();
	while(1){
		//UART0_SendString((uint8_t *)"Hello World\n");
		Delay();
		//count1 = count;

	}
}