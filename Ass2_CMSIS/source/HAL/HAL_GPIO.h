/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "Driver_GPIO.h"

/*******************************************************************************
* Prototypes
*******************************************************************************/
/*
 * @brief: Initial Led Pin
 *
 */
void HAL_GPIO_Init(FGPIO_Type* fgpio, uint8_t pin);

/**
 * @brief Delay for approximately 200 microseconds
 *
 * This function creates a delay of approximately 200 microseconds
 * by running a loop with NOP instructions.
 */
void HAL_GPIO_Delay200us();

/**
 * @brief Delay for approximately 1 second
 *
 * This function creates a delay of approximately 1 second
 * by running a loop with NOP instructions.
 */
void HAL_GPIO_Delay1s();

/**
 * @brief Generate a PWM-like signal for 2 seconds with a specific duty cycle
 *
 * This function toggles the LED pin on and off to simulate a PWM signal
 * for 2 seconds, with the LED on for a duration proportional to the duty cycle.
 *
 * @param duty The duty cycle percentage (0-100)
 */
void HAL_GPIO_Set_DutyCycle2s(uint32_t duty, FGPIO_Type* fgpio, uint8_t pin);

#endif // HAL_GPIO_H

/*******************************************************************************
* EOF
*******************************************************************************/
