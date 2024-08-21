/*******************************************************************************
* Includes
*******************************************************************************/
#include "uart.h"

/*******************************************************************************
* Variables
*******************************************************************************/
uint8_t string_PC[14] = "Hello from PC!";	/* String is sent from PC */
uint8_t comp_flag = 0; 						/* Flag to compare 2 characters -- 0 is TRUE */
uint8_t count = 0;							/* Count characters */
uint8_t receive_flag = 0;					/* if 2 strings are the same return 1 */

/*******************************************************************************
* Function
*******************************************************************************/
void initLED() {
	PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC_MASK;	/* Enable clock for port D*/
	PORTD->PCR[1] |= PCR_MUX_GPIO_Mask;			/* Configure MUX for PORT D */
	FGPIOD->PDDR |= 1 << BLUE_LED_PIN;			/* Configure direction output for LED blue */
	FGPIOD->PDOR &= ~(1 << BLUE_LED_PIN);		/* Configure on for LED blue */
}

void initUART0() {
	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1); 	/* Configure clock for PORT B */
	PORTB->PCR[0] |= PORT_PCR_MUX(2); 			/* Configure UART for PCR 0 -- 0b010 << 8 */
	PORTB->PCR[1] |= PORT_PCR_MUX(2); 			/* Configure UART for PCR 1 -- 0b010 << 8 */

	/* Configure Clock for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3); 	/* Configure FIRCDIV for UART0 */
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_CGC(1); 	/* Enable clock for UART0 */
	SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(1); 		/* 1 << 8 */

	/* Configure UART */
	LPUART0->CTRL &= ~(1 << 19 | 1 << 18); /* Disable TE & RE while configuring*/
	LPUART0->CTRL &= ~(1 << 4); /* 8-bit mode select */
	LPUART0->STAT &= ~(1 << 29); /* Set LSB for data transmission ->> bit start = 0 */
	LPUART0->BAUD &= ~(1 << 13); /* Configure for 1 stop bit */

	/* Set Baud Rate */
	LPUART0->BAUD |= 1 << 17; /* Set BOTHEDGE */
	LPUART0->BAUD &= ~(0b1011 << 24); /* Set OSR = 4 -> OSR + 1 = 5 */
	LPUART0->BAUD = (LPUART0->BAUD & ~(1 << 2)) | LPUART_BAUD_SBR(SystemCoreClock / (BaudRate_UART * 5)); /* SBR = 1000 */

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

uint8_t check_receive(){
	uint8_t data = 0;
		if(count == 14){
			count = 0;
		}
		data = LPUART0->DATA & 0xFF;

		if(data != string_PC[count]){
			comp_flag = 1;
		}
		count ++;

		if(comp_flag == 0) {
			if (count == 14) {
				receive_flag = 1;
			}
			else {
				/* Do nothing */
				receive_flag = 0;
			}
		}
		else {
			comp_flag = 0;
			count = 0;
		}
		return receive_flag;
}
/*******************************************************************************
* EOF
*******************************************************************************/
