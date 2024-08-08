/*******************************************************************************
* Include
*******************************************************************************/
#include "Driver_GPIO.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define DELAY_CNT_1s            (3750000)
#define DELAY_CNT_200us         ((DELAY_CNT_1s / 10000) * 2) // = 750
#define GREEN_LED_PIN           (1 << 4)

/*******************************************************************************
* Functions
*******************************************************************************/
void Driver_GPIO_InitLed() {
    PCC->CLKCFG[PCC_PORTB_INDEX] |= 1 << 30;	/* Enable clock for Port B */
    PORTB->PCR[4] |= 1 << 8;			/* Configure PTB4 as a GPIO pin */
    FGPIOB->PDDR |= GREEN_LED_PIN ;		/* Set PTB4 as an output */
    FGPIOB->PDOR |= GREEN_LED_PIN ;		/* Turn led off */
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

void Driver_GPIO_Toggle() {
    FGPIOB->PTOR |= GREEN_LED_PIN;	/* Tonggle the LED */
}

/*******************************************************************************
* EOF
*******************************************************************************/
