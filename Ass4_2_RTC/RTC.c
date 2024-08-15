#include "MKE16Z4.h"

#define GREEN_LED_PIN			4
#define BLUE_LED_PIN			1
#define PCR_MUX_GPIO_Mask		1 << 8

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
	RTC->SR &= ~RTC_SR_TCE_MASK;
}

int main() {

}
