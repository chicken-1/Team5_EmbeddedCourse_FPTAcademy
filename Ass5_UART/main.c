#include "uart.h"

uint8_t countSystick = 0; 	/* Count ticks in 1 second */

void SysTick_Handler() {
	if(countSystick == 4) {
		UART0_SendString((uint8_t *)"Hello from MKE16Z!\n");
		countSystick = 0;
	}
	else {
		countSystick++;
	}
}

void LPUART0_IRQHandler() {
	if(check_receive()){
		FGPIOD->PTOR |= 1 << BLUE_LED_PIN;
	}
}
int main () {
	initUART0();
	initLED();
	SysTick_Config(SystemCoreClock / 4); /* 250ms */

	while(1){

	}
}
