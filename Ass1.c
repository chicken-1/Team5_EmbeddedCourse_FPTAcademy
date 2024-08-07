#include "MKE16Z4.h"

#define DELAY_CNT_1s            (3750000)
#define DELAY_CNT_200us			((DELAY_CNT_1s / 10000) * 2) // = 750
#define GREEN_LED_PIN           (1 << 4)

void initLed();
void delay_200us();
void delay_1s();
void duty_cycle_2s();
void mode1();
void mode2();

int main() {
	initLed();
	while(1){
		mode1();
		mode2();
	}
}

void initLed() {
	/* Configure clock for PORTB */
	PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;

	/* Configure MUX for PCR_4 */
	PORTB->PCR[4] |= 1 << 8;

	/* Set bit for PDOR */
	FGPIOB->PDDR |= 1 << 4;
	FGPIOB->PDOR |= 1 << 4;
	/* Or
	 * FGPIOB->PSOR |= 1 << 4;
	 */
}

/* 100hz -> period = 20ms -> 1% = 200us */
void delay_200us() {
	uint32_t index;
	for(index = 0; index < DELAY_CNT_200us; index++) {
		__asm("nop");
	}
}

void delay_1s() {
	uint32_t index;
	for(index = 0; index < DELAY_CNT_1s; index++) {
		__asm("nop");
	}
}

void duty_cycle_2s(uint32_t duty) {
	uint32_t index;
	
	FGPIOB->PTOR |= 1 << 4;
	for(index = 1; index <= duty; index++) {
			delay_200us();
	}

	FGPIOB->PTOR = 1 << 4;
	for(index = 1; index <= 100 - duty; index++) {
		delay_200us();
	}
}

void mode1() {
	uint32_t count_ms = 0;
	uint32_t duty;
	uint8_t on = 0;
	while(count_ms < 8) {
		duty = 1;
		if(on == 0) {
			/* LED OFF */
			FGPIOB->PDOR |= 1 << 4;
			
			/* if LED OFF then change the state so that the LED gradually brightens */
			while(duty <= 100) {
			duty_cycle_2s(duty);
			duty++;
			}
			on = 1;
		} 
		else {
			/* LED ON */
			FGPIOB->PDOR &= ~(1 << 4);
			
			/* if LED ON then change the state so that the LED fades out */
			while(duty <= 100) {
			duty_cycle_2s(duty);
			duty++;
			}
			on = 0;
		}
		count_ms += 2;
	}
}

void mode2() {
	uint32_t count_ms = 0;
	while(count_ms < 8) {
		FGPIOB->PTOR |= 1 << 4;
		delay_1s();
		count_ms++;
	}
}
