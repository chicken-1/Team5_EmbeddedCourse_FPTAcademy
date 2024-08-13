#include "Interrupt.h"

#define PCR_MUX_GPIO_Mask		1 << 8
#define PCC_CGC_Mask			1 << 30
#define GREEN_LED_PIN			4

void Init_GREEN_LED() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CGC_Mask;	/* Enable clock for Port B */
	PORTB->PCR[4] |= PCR_MUX_GPIO_Mask;				/* Configure PTB4 as a GPIO pin */
	FGPIOB->PDDR |= 1 << GREEN_LED_PIN;				/* Set PTB4 as an output */
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;				/* Turn led off */
}

void InitSW3() {
	PCC->CLKCFG[PCC_PORTD_INDEX] |= 1 << 30;

	PORTD->PCR[2] |= PCR_MUX_GPIO_Mask;
	GPIOD->PDDR &= ~(1 << 2);
	PORTD->PCR[2] |= PORT_PCR_IRQC(10);
	__NVIC_EnableIRQ(PORTBCD_IRQn);
}

void mode1(){

}

void mode2() {

}

void mode3() {

}
