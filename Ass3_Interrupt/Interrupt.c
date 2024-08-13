#include "Interrupt.h"

#define PCR_MUX_GPIO_Mask		1 << 8
#define PCC_CGC_Mask			1 << 30
#define GREEN_LED_PIN			4

uint32_t ticks_mode3 = 1;
uint32_t duty = 1;

void Init_GREEN_LED() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CGC_Mask;	/* Enable clock for Port B */
	
	PORTB->PCR[4] |= PCR_MUX_GPIO_Mask;				/* Configure PTB4 as a GPIO pin */
	FGPIOB->PDDR |= 1 << GREEN_LED_PIN;				/* Set PTB4 as an output */
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;				/* Turn led off */
}

void InitSW3() {
	PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CGC_Mask;	/* Enable clock for Port D */

	PORTD->PCR[2] |= PCR_MUX_GPIO_Mask;				/* Configure PTD2 as a GPIO pin */
	GPIOD->PDDR &= ~(1 << 2);						/* Set PTD2 as an input */
	PORTD->PCR[2] |= PORT_PCR_IRQC(10);				/* Configure IRQ - falling edge */
	
	PORTD->PCR[Button_PIN] |= (1 << 24); 			/* Delete Interrupt flag status */
	/* PORTD->ISFR |= 1 << Button_PIN */
	
	__NVIC_EnableIRQ(PORTBCD_IRQn);					/* Enable Interrupt - PORT BCD */
}

void mode1(){
	FGPIOB->PDOR &= ~(1 << GREEN_LED_PIN);
}

void mode2() {
	FGPIOB->PTOR |= 1 << GREEN_LED_PIN;
}

void mode3() {
	if(duty <= ticks_mode3) {
		FGPIOB->PDOR &= ~(1 << 4);
		duty++;
	}
	else {
		FGPIOB->PDOR |= 1 << 4;
		duty++;
	}

	if(duty == 101) {
		duty = 1;
		ticks_mode3++;
	}
	if(ticks_mode3 == 101) {
		ticks_mode3 = 1;
	}
}

void stop_mode() {
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;
}
