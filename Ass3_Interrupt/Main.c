#include "Interrupt.h"

typedef enum {
	MODE1,
	MODE2,
	MODE3,
	STOP_MODE,
} mode;

mode current_mode = STOP_MODE;

void PORTBCD_IRQHandler(void) {
	// Clear ISF flag
	PORTD->PCR[2] |= 1 << 24;

	// mode conversation
	if (current_mode == STOP_MODE) {
		current_mode = MODE1;
	}
	else if (current_mode == MODE1) {
		current_mode = MODE2;
	}
	else if (current_mode == MODE2) {
		current_mode = MODE3;
	}
	else {
		current_mode = STOP_MODE;
	}
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

int main() {
	Init_GREEN_LED();
	InitSW3();
	SysTick_Config(19200);

	while(1) {

	}
}
