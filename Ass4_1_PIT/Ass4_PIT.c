/*******************************************************************************
* Include
*******************************************************************************/
#include "PIT.h"

/*******************************************************************************
* Variables
*******************************************************************************/
static uint32_t greenCounter = 0;
static uint32_t blueCounter = 0;
static uint8_t changeFlag = 0;
static uint8_t pitFlag = 0;

/*******************************************************************************
* Prototypes
*******************************************************************************/
/**
 * @brief Interrupt handling for LPI0
 */
void LPIT0_IRQHandler();

/**
 * @brief LED control function
 *
 * Control flashing green led on for 1 second and red led on for 2.35 seconds
 */
void Led_Handler();

/*******************************************************************************
* Main
*******************************************************************************/
int main() {
	initLed();
	initPIT();

	while(1) {
		if(pitFlag == 1) {
			pitFlag = 0;
			Led_Handler();
		}
	}
}

/*******************************************************************************
* Functions
*******************************************************************************/
void LPIT0_IRQHandler() {
	LPIT0->MSR |= 1 << 0;

	pitFlag = 1;
}

void Led_Handler(){
	/* Flag = 0 -> green led on 1s -- timer value = 50ms -> run 20 times */
	if(changeFlag == 0) {
		setGreenLed();
		greenCounter++;
		if(greenCounter == 21) {
			changeFlag = 1;
			greenCounter = 0;
		}
	}
	/* Flag = 1 -> blue led on 2.35s -- timer value = 50ms -> run 47 times */
	else {
		setBlueLed();
		blueCounter++;
		if(blueCounter == 48) {
			changeFlag = 0;
			blueCounter = 0;
		}
	}
}

/*******************************************************************************
* EOF
*******************************************************************************/
