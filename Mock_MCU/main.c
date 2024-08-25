/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"
#include "Srec.h"
#include "flash.h"

/*******************************************************************************
* Variables
*******************************************************************************/
#define SystemCoreClock		48000000
#define BaudRate_UART		9600

uint8_t queue[4][256];
uint8_t temp_queue[256];
uint8_t push_index = 0;		/* index of queue that data will be pushed in */
uint8_t element_index = 0;	/* index of element in queue */
uint8_t pop_index = 0;		/* index of queue being handled then popped out */
uint8_t queue_element = 0;	/* number of unhandled queues */
error_t error_check = ERR_NONE;
uint8_t first_flag = FALSE;
uint8_t terminate_flag = FALSE;

/*******************************************************************************
* Function
*******************************************************************************/
void clear(uint8_t queueIndex){
	uint8_t index = 0; /* index of element in a queue*/

	while(queue[queueIndex][index] != '\0') {
		queue[queueIndex][index] = '\0';
		index++;
	}
}

void init_queue() {
	for(int i =0; i < 4; i++){
		clear(i);
	}
}

void clear_temp() {
	uint8_t index = 0; /* index of element in a queue*/

	while(temp_queue[index] != '\0') {
		temp_queue[index] = '\0';
		index++;
	}
}

void push_queue(uint8_t data){
	if(data == '\n') {
		push_index++;
		queue_element++;

		if(push_index == 4){
			push_index = 0;
		}
		element_index = 0;

	}
	else if(data == '\r') {
		/*do nothing*/
	}
	else {
		queue[push_index][element_index] = data;
		element_index++;
	}
}

void parse_queue(uint8_t* line){
	if(first_flag == FALSE) {
		if(!check_Record_Start(line)){
			error_check = ERR_RECORD_START;
		}
		else {
			/* Do nothing */
		}
		first_flag = TRUE;
	}
	else {
		/* Do nothing */
	}

	if(!check_Hex(line)) {
		error_check = ERR_HEX;
	}
	else {
		/* Do nothing */
	}

	if(!check_S(line)) {
		error_check = ERR_S_TYPE;
	}
	else {
		/* Do nothing */
	}

	if(!check_Bytecount(line)) {
		error_check = ERR_BYTE_COUNT;
	}
	else {
		/* Do nothing */
	}

	if(!check_Sum(line)) {
		error_check = ERR_CHECK_SUM;
	}
	else {
		/* Do nothing */
	}
	if(!check_Terminate(line)) {
			error_check = ERR_TERMINATE;
	}
	else {
		/* Do nothing */
	}
}

void pop_queue(){
	if(queue_element > 0){
		strcpy((char*)temp_queue, (char*)queue[pop_index]);

		parse_queue(queue[pop_index]);
		queue_element--;

		if((queue[pop_index][1] == '9') || (queue[pop_index][1] == '8')
				|| (queue[pop_index][1] == '7')) {
			terminate_flag = TRUE;
			first_flag = FALSE;
		}

		clear(pop_index);
		pop_index++;

		if(pop_index == 4) {
			pop_index = 0;
		}
		else {
			/* Do nothing */
		}
	}
	else {
		/* Do nothing */
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

	data = LPUART0->DATA & 0xFF;
	push_queue(data);
}

void Delay()
{
	uint32_t index = 0;

	for(index = 0; index < 37500000/500; index++){
		__asm("nop");
	}
}

int main () {
	initUART0();
	init_queue();

	while(1) {
		pop_queue();
		switch(error_check) {
			case ERR_RECORD_START:
				UART0_SendString((uint8_t*)"Error Record Start!\n");
				break;
			case ERR_HEX:
				UART0_SendString((uint8_t*)"Error Check Hex!\n");
				break;
			case ERR_S_TYPE:
				UART0_SendString((uint8_t*)"Error Check S!\n");
				break;
			case ERR_BYTE_COUNT:
				UART0_SendString((uint8_t*)"Error Check ByteCount!\n");
				break;
			case ERR_CHECK_SUM:
				UART0_SendString((uint8_t*)"Error Check Sum!\n");
				break;
			case ERR_TERMINATE:
				UART0_SendString((uint8_t*)"Error Check Terminate!\n");
				break;
			default:
				if(temp_queue[0] !=  '\0'){
					get_Data(temp_queue);
					get_Address(temp_queue);
					UART0_SendString(data);
					UART0_SendString("    ");
					UART0_SendString(address);
					//UART0_SendString(temp_queue);
					UART0_SendChar('\n');
				}
				else {
					/* Do nothing */
				}
				break;
		}
		error_check = ERR_NONE;
		clear_temp();

		if(terminate_flag == TRUE){
			init_queue();
			terminate_flag = FALSE;
			push_index = 0;
			pop_index = 0;
		}
	}
}

/*******************************************************************************
* EOF
*******************************************************************************/
