/*******************************************************************************
* Include
*******************************************************************************/
#include "Interrupt.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define TRUE 1
#define FALSE 0

static mode current_mode = STOP_MODE;
static uint8_t mode_change_flag = FALSE;

/*******************************************************************************
* Prototypes
*******************************************************************************/
uint32_t SysTick_Config_User(uint32_t ticks);

void PORTBCD_IRQHandler(void);

void SysTick_Handler(void);

/*******************************************************************************
* Main
*******************************************************************************/
int main() {
	Init_GREEN_LED();
	InitSW3();
	SysTick_Config_User(19200); /* 19200 ticks = 400us */

	while(1) {
		/* Check mode flag	 */
		if(mode_change_flag) {
			/* Delete flag */
			mode_change_flag = FALSE;

			switch(current_mode) {
			case STOP_MODE:
				current_mode = MODE1;
				break;
			case MODE1:
				current_mode = MODE2;
				break;
			case MODE2:
				current_mode = MODE3;
				break;
			case MODE3:
				current_mode = STOP_MODE;
				break;
			default:
				break;
			}
		}
	}
}

/*******************************************************************************
* Functions
*******************************************************************************/
uint32_t SysTick_Config_User(uint32_t ticks) {
	SysTick->LOAD = ticks - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = (1 << 2) | (1 << 1) | ( 1 << 0);
}

void PORTBCD_IRQHandler() {
	/* Clear ISF flag */
	PORTD->PCR[2] |= 1 << 24;
	/* Set flag to indicate mode change */
	mode_change_flag = TRUE;
}

void SysTick_Handler() {
	if (current_mode == MODE1) {
		mode1();
	}
	else if (current_mode == MODE2) {
		mode2();
	}
	else if (current_mode == MODE3) {
		mode3();
	}
	else {
		stop_mode();
	}
}

/*******************************************************************************
* EOF
*******************************************************************************/
