/*******************************************************************************
* Include
*******************************************************************************/
#include "HAL_GPIO.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define DELAY_CNT_1s            (3750000)
#define DELAY_CNT_200us         ((DELAY_CNT_1s / 10000) * 2) /* = 750 */

/*******************************************************************************
* Functions
*******************************************************************************/
void HAL_GPIO_Init(FGPIO_Type* fgpio, uint8_t pin) {
	uint8_t pcc_port_index = 0;
	PORT_Type* port;

	if (fgpio == FGPIOA) {
		pcc_port_index = PCC_PORTA_INDEX;
		port = PORTA;
	}
	else if (fgpio == FGPIOB) {
		pcc_port_index = PCC_PORTB_INDEX;
		port = PORTB;
	}
	else if (fgpio == FGPIOC) {
		pcc_port_index = PCC_PORTC_INDEX;
		port = PORTC;
	}
	else if (fgpio == FGPIOD) {
		pcc_port_index = PCC_PORTD_INDEX;
		port = PORTD;
	}
	else {
		pcc_port_index = PCC_PORTE_INDEX;
		port = PORTE;
	}
    Driver_GPIO_CLK(pcc_port_index);
    Driver_GPIO_MUX(port, pin);
    Driver_GPIO_Direction_Output(fgpio, pin);
    Driver_GPIO_Output_Set(fgpio, pin);
}

void HAL_GPIO_Delay200us() {
    uint32_t index;

    for(index = 0; index < DELAY_CNT_200us; index++) {
        __asm("nop");
    }
}

void HAL_GPIO_Delay1s() {
    uint32_t index;

    for(index = 0; index < DELAY_CNT_1s; index++) {
        __asm("nop");
    }
}

void HAL_GPIO_Set_DutyCycle2s(uint32_t duty, FGPIO_Type* fgpio, uint8_t pin) {
	uint32_t index;

	Driver_GPIO_Toggle(fgpio, pin);
	for(index = 1; index <= duty; index++) {
	    HAL_GPIO_Delay200us();
	}
	Driver_GPIO_Toggle(fgpio, pin);
	for(index = 1; index <= 100 - duty; index++) {
	    HAL_GPIO_Delay200us();
	}
}

/*******************************************************************************
* EOF
*******************************************************************************/
