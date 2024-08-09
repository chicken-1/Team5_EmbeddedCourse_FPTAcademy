/*******************************************************************************
* Include
*******************************************************************************/
#include "Driver_GPIO.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define PCR_MUX_GPIO_Mask		1 << 8
#define PCC_CGC_Mask			1 << 30

/*******************************************************************************
* Functions
*******************************************************************************/
void Driver_GPIO_CLK(uint8_t pcc_port_index) {
	PCC->CLKCFG[pcc_port_index] |= PCC_CGC_Mask;
}

void Driver_GPIO_MUX(PORT_Type* port, uint8_t pin) {
	port->PCR[pin] |= PCR_MUX_GPIO_Mask;
}

void Driver_GPIO_Direction_Output(FGPIO_Type* fgpio, uint8_t pin) {
	fgpio->PDDR |= 1 << pin;
}

void Driver_GPIO_Output_Set(FGPIO_Type* fgpio, uint8_t pin) {
	fgpio->PDOR |= 1 << pin;
}

void Driver_GPIO_Output_Reset(FGPIO_Type* fgpio, uint8_t pin) {
	fgpio->PDOR &= ~(1 << pin);
}

void Driver_GPIO_Toggle(FGPIO_Type* fgpio, uint8_t pin) {
    fgpio->PTOR |= 1 << pin;	/* Toggle the LED */
}

/*******************************************************************************
* EOF
*******************************************************************************/
