/*******************************************************************************
* Includes
*******************************************************************************/
#include "uart.h"

/*******************************************************************************
* Variables
*******************************************************************************/
uint8_t countSystick = 0; 	/* Count ticks in 1 second */

/*******************************************************************************
* Prototypes
*******************************************************************************/

/**
 * @brief SysTick interrupt handler.
 *
 * This function handles the SysTick timer interrupt. It increments the
 * `countSystick` variable every 250ms. When the counter reaches 4,
 * it sends a message over UART0 and resets the counter.
*/
void SysTick_Handler();

/**
 * @brief UART0 interrupt handler.
 *
 * This function handles the UART0 interrupt. It checks if a byte has been
 * received via UART0 using the `check_receive` function. If a byte is received,
 * it toggles the BLUE LED by inverting the state of the corresponding GPIO pin.
 */
void LPUART0_IRQHandler();

/*******************************************************************************
* Main function
*******************************************************************************/
int main () {
	initUART0();
	initLED();
	SysTick_Config(SystemCoreClock / 4); /* 250ms */

	while(1){

	}
}

/*******************************************************************************
* Function
*******************************************************************************/
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

/*******************************************************************************
* EOF
*******************************************************************************/
