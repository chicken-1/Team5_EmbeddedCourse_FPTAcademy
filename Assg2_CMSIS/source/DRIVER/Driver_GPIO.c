/*******************************************************************************
* Include
*******************************************************************************/
#include "Driver_GPIO.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define DELAY_CNT_1s            (3750000)
#define DELAY_CNT_200us         ((DELAY_CNT_1s / 10000) * 2) /* = 750 */

/*******************************************************************************
* Functions
*******************************************************************************/
/*
void Driver_GPIO_InitLed() {
    PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;	 Enable clock for Port B
    PORTB->PCR[4] |= 1 << 8;			 Configure PTB4 as a GPIO pin
    FGPIOB->PDDR |= 1 << 4 ;		 Set PTB4 as an output
    FGPIOB->PDOR |= 1 << 4 ;		 Turn led off
}
*/

void Driver_GPIO_CLK(uint8_t pcc_port_index) {
	PCC->CLKCFG[pcc_port_index] |= 1 << 30;
}

void Driver_GPIO_MUX(PORT_Type* port, uint8_t pin) {
	port->PCR[pin] |= 1 << 8;
}

void Driver_GPIO_Direction_Output(FGPIO_Type* fgpio, uint8_t bit) {
	fgpio->PDDR |= 1 << bit;
}

void Driver_GPIO_Output_OFF(FGPIO_Type* fgpio, uint8_t bit) {
	fgpio->PDOR |= 1 << bit;
}

void Driver_GPIO_Output_ON(FGPIO_Type* fgpio, uint8_t bit) {
	fgpio->PDOR &= ~(1 << bit);
}

void Driver_GPIO_Toggle(FGPIO_Type* fgpio, uint8_t bit) {
    fgpio->PTOR |= 1 << bit;	/* Toggle the LED */
}

void Driver_GPIO_Delay200us() {
    uint32_t index;

    for(index = 0; index < DELAY_CNT_200us; index++) {
        __asm("nop");
    }
}

void Driver_GPIO_Delay1s() {
    uint32_t index;

    for(index = 0; index < DELAY_CNT_1s; index++) {
        __asm("nop");
    }
}

/*
void Driver_GPIO_DutyCycle2s(uint32_t duty) {
    uint32_t index;

    Driver_GPIO_Toggle();
    for(index = 1; index <= duty; index++) {
        Driver_GPIO_Delay200us();
    }
    Driver_GPIO_Toggle();
    for(index = 1; index <= 100 - duty; index++) {
        Driver_GPIO_Delay200us();
    }
}
*/

/*******************************************************************************
* EOF
*******************************************************************************/
