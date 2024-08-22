/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
* Variables
*******************************************************************************/
#define SystemCoreClock		48000000
#define BaudRate_UART		9600

volatile uint8_t queue[4][255];
volatile uint8_t push_index = 0;
volatile uint8_t element_index = 0;
volatile uint8_t pop_index = 0;
volatile uint8_t queue_element = 0;
volatile uint8_t error_check = 0;
/*******************************************************************************
* Function
*******************************************************************************/

void clear(uint8_t index){
	uint8_t j = 0;
	while(queue[index][j] != '\0'){
		queue[index][j] = '\0';
		j++;
	}
}

void push_queue(uint8_t data){
	if(data == '\n'){
		push_index++;
		queue_element++;  // breakpoint debug

		if(push_index == 4){
			push_index = 0;
		}
		//clear(push_index);
		element_index = 0;

	}else if(data == '\r'){
		/*do nothing*/
	}else{
		queue[push_index][element_index] = data;
		element_index++;
	}
}

void check_S(uint8_t* line){
	if(line[0] != 'S'){
		error_check = 1;
	}
}

void parse_queue(uint8_t* line){
	/*Check error ...*/
	check_S(line);
}

void pop_queue(){
	if(queue_element > 0){
		parse_queue(queue[pop_index]);
		queue_element--;
		clear(pop_index);
		pop_index++;
		if(pop_index == 4){
			pop_index = 0;
		}
	}
}

void initUART0() {
	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1); /* Configure clock for PORT B */
	PORTB->PCR[0] |= PORT_PCR_MUX(2); /* Configure UART for PCR 0 -- 0b010 << 8 */
	PORTB->PCR[1] |= PORT_PCR_MUX(2); /* Configure UART for PCR 1 -- 0b010 << 8 */

	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3); /* Configure FIRCDIV for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_CGC(1); /* Enable clock for UART0 */
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1); /* 1 << 8 */

	/* Configure UART */
	LPUART0->CTRL &= ~(1 << 19 | 1 << 18); /* Disable TE & RE while configuring*/
	LPUART0->CTRL &= ~(1 << 4); /* 8-bit mode select */
	LPUART0->STAT &= ~(1 << 29); /* Set LSB for data transmission ->> bit start = 0 */
	LPUART0->BAUD &= ~(1 << 13); /* Configure for 1 stop bit */

	/* Set Baud Rate */
	LPUART0->BAUD |= 1 << 17; /* Set BOTHEDGE */
	LPUART0->BAUD &= ~(0b1011 << 24); /* Set OSR = 4 -> OSR + 1 = 5 */
	LPUART0->BAUD = (LPUART0->BAUD & ~(1 << 2)) |
			LPUART_BAUD_SBR(SystemCoreClock / (BaudRate_UART * 5)); /* SBR = 1000 */

	/* Enable Receiver interrupt */
	LPUART0->CTRL |= 1 << 21; /* Configure RIE */
	NVIC_EnableIRQ(LPUART0_IRQn); /* Enable interrupt */

	/* Enable transmit & receive */
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
	uint8_t flag = 0;
	data = LPUART0->DATA & 0xFF;

	//UART0_SendChar(data);
	if (data != '\0') {
		push_queue(data);
	}
	//pop_queue();
}

void Delay()
{
	uint32_t index;
	for(index = 0; index < 37500000/5; index++){
		__asm("nop");
	}
}


int main () {
	initUART0();
	/*flag file ready*/
	//Delay();
//	for(uint8_t index = 0; index < 4; index ++){
//		while(queue[index][j] != '\0'){
//			UART0_SendChar(queue[index][j]);
//			j++;
//		}
//			UART0_SendChar('\n');
//		j = 0;
//	}

	while(1) {
		/*check flag file ready*/
		/*pop_queue*/
		if(error_check == 1){
			UART0_SendChar('E');
			error_check = 0;
		}
	}
}
/*******************************************************************************
* EOF
*******************************************************************************/
