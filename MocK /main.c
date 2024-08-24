/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"
#include "function.h"

/*******************************************************************************
* Variables
*******************************************************************************/
#define SystemCoreClock		48000000
#define BaudRate_UART		9600

uint8_t queue[4][255];
uint8_t temp_queue[255];
uint8_t push_index = 0;
uint8_t element_index = 0;
uint8_t pop_index = 0;
uint8_t queue_element = 0;
uint8_t error_check = 0;
uint8_t first_flag = 0;
uint8_t count = 0;
uint8_t terminate_flag = 0;

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

void clear_temp() {
	uint8_t index = 0;

	while(temp_queue[index] != '\0') {
		temp_queue[index] = '\0';
		index++;
	}
}

void init_queue(){
	for(int i =0; i < 4; i++){
		clear(i);
	}
}

void push_queue(uint8_t data){
	if(data == '\n'){
		push_index++;
		queue_element++;

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


void parse_queue(uint8_t* line){
	if(first_flag == 0){
		if(!check_Record_Start(line)){
			error_check = 1;
			first_flag = 1;
		}
	}

	if(!check_Hex(line)) {
		error_check = 2;
	}

	if(!check_S(line)) {
		error_check = 3;
	}

	if(!check_Bytecount(line)) {
		error_check = 4;
	}

	if(!Check_Sum(line)) {
		error_check = 5;
	}

	if(!check_Terminate(line, pop_index)) {
		error_check = 6;
		terminate_flag = 1;
		first_flag = 0;
	}
}

void pop_queue(){
	if(queue_element > 0){
		strcpy((char*)temp_queue, (char*)queue[pop_index]);
		parse_queue(queue[pop_index]);
		queue_element--;

		if((queue[pop_index][1] == '9') || (queue[pop_index][1] == '8') || (queue[pop_index][1] == '7')){
			terminate_flag = 1;
			first_flag = 0;
		}

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
	data = LPUART0->DATA & 0xFF;

	push_queue(data);
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
	init_queue();

	while(1) {
		pop_queue();
		switch(error_check) {
			case 1:
				UART0_SendString((uint8_t*)"Error Record Start !\n");
				break;
			case 2:
				UART0_SendString((uint8_t*)"Error Check Hex !\n");
				break;
			case 3:
				UART0_SendString((uint8_t*)"Error Check S !\n");
				break;
			case 4:
				UART0_SendString((uint8_t*)"Error Check ByteCount !\n");
				break;
			case 5:
				UART0_SendString((uint8_t*)"Error Check Sum !\n");
				break;
			case 6:
				UART0_SendString((uint8_t*)"Error Check Terminate !\n");
				break;
			default:
				UART0_SendString(temp_queue);
				UART0_SendChar('\n');
				break;
		}

		clear_temp();

		if(terminate_flag == 1){
			init_queue();
			terminate_flag = 0;
			push_index = 0;
			pop_index = 0;
		}
	}
}
/*******************************************************************************
* EOF
*******************************************************************************/