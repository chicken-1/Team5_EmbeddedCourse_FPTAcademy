/*******************************************************************************
* Include
*******************************************************************************/
#include "APP_GPIO.h"

/*******************************************************************************
* Functions
*******************************************************************************/
void APP_GPIO_Mode1(FGPIO_Type* fgpio, uint8_t pin) {
    uint32_t count_ms = 0;
    uint32_t duty = 0;

    while (count_ms < 8) {
        for (duty = 1; duty <= 100; duty++) {
        	HAL_GPIO_Set_DutyCycle2s(duty, fgpio, pin);
        }
        for (duty = 100; duty > 0; duty--) {
        	HAL_GPIO_Set_DutyCycle2s(duty, fgpio, pin);
        }
        count_ms += 4;
    }
}

void APP_GPIO_Mode2(FGPIO_Type* fgpio, uint8_t pin) {
    uint32_t count_ms = 0;

    while (count_ms < 8) {
        Driver_GPIO_Toggle(fgpio, pin);
        HAL_GPIO_Delay1s();
        count_ms++;
    }
}

/*******************************************************************************
* EOF
*******************************************************************************/
