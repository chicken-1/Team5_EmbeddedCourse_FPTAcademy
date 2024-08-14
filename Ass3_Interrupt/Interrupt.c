/*******************************************************************************
* Include
*******************************************************************************/
#include "Interrupt.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define PCR_MUX_GPIO_Mask		1 << 8
#define PCC_CGC_Mask			1 << 30
#define GREEN_LED_PIN			4
#define BUTTON_PIN				2
#define MODE2_DURATION_TICKS	4800000 /* 100ms = 4800000 ticks */

static uint32_t duty_cycle = 1;
static uint32_t duty = 1;
static uint32_t ticks_mode2 = 0;

/*******************************************************************************
* Functions
*******************************************************************************/
void Init_GREEN_LED() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CGC_Mask;	/* Enable clock for Port B */

	PORTB->PCR[4] |= PCR_MUX_GPIO_Mask;				/* Configure PTB4 as a GPIO pin */
	FGPIOB->PDDR |= 1 << GREEN_LED_PIN;				/* Set PTB4 as an output */
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;				/* Turn led off */
}

void InitSW3() {
	PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CGC_Mask;	/* Enable clock for Port D */

	PORTD->PCR[2] |= PCR_MUX_GPIO_Mask;	/* Configure PTD2 as a GPIO pin */
	FGPIOD->PDDR &= ~(1 << BUTTON_PIN);				/* Set PTD2 as an input */
	PORTD->PCR[2] |= PORT_PCR_IRQC(10);	/* Configure IRQ - falling edge */

	PORTD->PCR[2] |= 1 << 24; 				/* Delete Interrupt flag status */
	__NVIC_EnableIRQ(PORTBCD_IRQn);					/* Enable Interrupt - PORT BCD */
}

void mode1(){
	FGPIOB->PDOR &= ~(1 << GREEN_LED_PIN);
}

void mode2() {
	if (ticks_mode2 == MODE2_DURATION_TICKS) {
		FGPIOB->PTOR |= 1 << GREEN_LED_PIN;
		ticks_mode2 = 0;
	}
	else {
		ticks_mode2 += 19200; 	/* 19200 ticks = 400us */
	}
}

void mode3() {
	if(duty <= duty_cycle) {
		FGPIOB->PDOR &= ~(1 << GREEN_LED_PIN);
		duty++;
	}
	else {
		FGPIOB->PDOR |= 1 << GREEN_LED_PIN;
		duty++;
	}

	if(duty == 101) {
		duty = 1;
		duty_cycle++;
	}
	else {
		/* Do nothing */
	}

	if(duty_cycle == 101) {
		duty_cycle = 1;
	}
	else {
		/* Do nothing */
	}
}

void stop_mode() {
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;
}

/*******************************************************************************
* EOF
*******************************************************************************/
