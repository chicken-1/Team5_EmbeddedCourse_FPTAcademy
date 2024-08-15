#include "MKE16Z4.h"

#define GREEN_LED_PIN			4
#define BLUE_LED_PIN			1

static uint32_t greenCounter = 0;
static uint32_t blueCounter = 0;
static uint32_t changeFlag = 0;

void initLed() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;
	PCC->CLKCFG[PCC_PORTD_INDEX] |= 1 << 30;

	/* Configure MUX for PORT B & D */
	PORTB->PCR[4] |= 1 << GREEN_LED_PIN;
	PORTD->PCR[1] |= 1 << BLUE_LED_PIN;

	/* Configure direction output for LED green & blue */
	FGPIOB->PDDR |= 1 << GREEN_LED_PIN;
	FGPIOD->PDDR |= 1 << BLUE_LED_PIN;

	/* Configure off for LED green & blue */
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;
	FGPIOD->PDOR |= 1 << BLUE_LED_PIN;
}

void initPIT() {
	PCC->CLKCFG[PCC_LPIT0_INDEX] |= 0b011 << 24; /* Configure pheriperial clock for LPIT */
	SCG->FIRCDIV |= 1 << 8;		/* configure div = 1 <=> Clock / 1 */

	LPIT0->MCR |= 1 << 1;		/* Timer channels and registers are reset */
	LPIT0->MCR &= ~(1 << 1);	/* Timer channels and registers are not reset */
	LPIT0->MCR |= 1 << 0;		/* Protocol clock to timers is enabled */

	LPIT0->CHANNEL[0].TCTRL |= LPIT_TCTRL_MODE(0); /* 0 << 2 -- 32-bit Periodic Counter */
	LPIT0->CHANNEL[0].TVAL |= (DEFAULT_SYSTEM_CLOCK / 20) - 1; /* 50ms */
	
	LPIT0->MIER |= LPIT_MIER_TIE0_MASK; /* 1 << 0 - interrupt enable generation*/
	NVIC_EnableIRQ(LPIT0_IRQn); /* interrupt enable */
	LPIT0->SETTEN |= LPIT_SETTEN_SET_T_EN_0_MASK; /* 1 << 0 -- Enables the Timer Channel 0 */
	/* Or LPIT0->CHANNEL[0].TCTRL |= 1 << 0 */
}

void LPIT0_IRQHandler() {
	LPIT0->MSR |= 1 << 0;

	/* Flag = 0 -> green led on 1s -- timer value = 50ms -> run 20 time */
	if(changeFlag == 0) {
		FGPIOD->PDOR &= ~(1 << GREEN_LED_PIN);
		FGPIOB->PDOR |= 1 << BLUE_LED_PIN;
		greenCounter++;
		if(greenCounter == 21) {
			changeFlag = 1;
			greenCounter = 0;
		}
	}
	/* Flag = 1 -> blue led on 2.35s -- timer value = 50ms -> run 47 time */
	else {
		FGPIOB->PDOR &= ~(1 << BLUE_LED_PIN);
		FGPIOD->PDOR |= 1 << GREEN_LED_PIN;
		blueCounter++;
		if(blueCounter == 48) {
			changeFlag = 0;
			blueCounter = 0;
		}
	}
}

int main() {
	initLed();
	initPIT();

	while(1) {}
}

