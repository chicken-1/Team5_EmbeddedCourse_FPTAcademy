
/*******************************************************************************
* Include
*******************************************************************************/
#include "HAL_GPIO.h"



/*******************************************************************************
* Functions
*******************************************************************************/
void HAL_GPIO_InitLed() {
    Driver_GPIO_InitLed();
}


void HAL_GPIO_Mode1() {
    uint32_t count_ms = 0;
    uint32_t duty = 0;

    while (count_ms < 8) {
        for (duty = 1; duty <= 100; duty++) {
        	Driver_GPIO_DutyCycle2s(duty);
        }
        for (duty = 100; duty > 0; duty--) {
        	Driver_GPIO_DutyCycle2s(duty);
        }
        count_ms += 4;
    }
}

void HAL_GPIO_Mode2() {
    uint32_t count_ms = 0;

    while (count_ms < 8) {
        Driver_GPIO_Toggle();
        Driver_GPIO_Delay1s();
        count_ms++;
    }
}

/*******************************************************************************
* EOF
*******************************************************************************/
