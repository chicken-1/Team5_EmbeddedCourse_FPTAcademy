#include "MKE16Z4.h"

#define GREEN_LED_PIN			4
#define BLUE_LED_PIN			1
#define PCR_MUX_GPIO_Mask		1 << 8

unsigned char led_green_on;
unsigned char led_green_off;
unsigned char led_blue_on;
unsigned char led_blue_off;

void initLED() {
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC_MASK;
	PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC_MASK;

	/* Configure MUX for PORT B & D */
	PORTB->PCR[4] |= PCR_MUX_GPIO_Mask;
	PORTD->PCR[1] |= PCR_MUX_GPIO_Mask;

	/* Configure direction output for LED green & blue */
	FGPIOB->PDDR |= 1 << GREEN_LED_PIN;
	FGPIOD->PDDR |= 1 << BLUE_LED_PIN;

	/* Configure off for LED green & blue */
	FGPIOB->PDOR |= 1 << GREEN_LED_PIN;
	FGPIOD->PDOR |= 1 << BLUE_LED_PIN;
}

void initRTC() {
	/* Configure clock for RTC */
	PCC->CLKCFG[PCC_RTC_INDEX] |= PCC_CLKCFG_CGC_MASK;

	/* Reset RTC by setting SWR bit and wait for TIF flag cleared */
	while(RTC->SR & RTC_SR_TIF_MASK) {
		RTC->CR |= RTC_CR_SWR_MASK;
		RTC->CR &= ~RTC_CR_SWR_MASK;
		RTC->TSR = 1;
	}

	/* Configure RTC: Enable the 1kHz LPO_CLK, disable the 32kHz oscillator */
	RTC->CR = (RTC_CR_LPOS(1)) | (RTC_CR_CPS(0)) |
			(RTC_CR_CPE(0)) | (RTC_CR_OSCE(0));

	/* Disable interrupts */
	RTC->IER = 0;
	/* Stop timer */
	RTC->TSR = 0;
	RTC->SR |= RTC_SR_TCE_MASK;
}

int main() {
	uint32_t previous_time = 0;
	uint32_t current_time = 0;

	initLED();
	initRTC();

	previous_time = RTC->TSR;
	current_time = RTC->TSR;
	while(1) {
		/* 5000? not for sure (try to delay 5s for green led)*/
		if ((current_time - previous_time) >= 1) {
			previous_time = current_time;
			FGPIOB->PTOR |= 1 << GREEN_LED_PIN;
		}
		else {
			current_time = RTC->TSR;
		}
	}
}
