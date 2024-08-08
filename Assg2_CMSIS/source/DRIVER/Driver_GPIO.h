/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include "MKE16Z4.h"

/*******************************************************************************
* Prototypes
*******************************************************************************/
/**
 * @brief Initialize the LED pin
 *
 * This function configures the necessary registers to initialize
 * the LED pin as an output and sets its initial state.
 */
void Driver_GPIO_InitLed();

/**
 * @brief Delay for approximately 200 microseconds
 *
 * This function creates a delay of approximately 200 microseconds
 * by running a loop with NOP instructions.
 */
void Driver_GPIO_Delay200us();

/**
 * @brief Delay for approximately 1 second
 *
 * This function creates a delay of approximately 1 second
 * by running a loop with NOP instructions.
 */
void Driver_GPIO_Delay1s();

/**
 * @brief Generate a PWM-like signal for 2 seconds with a specific duty cycle
 *
 * This function toggles the LED pin on and off to simulate a PWM signal
 * for 2 seconds, with the LED on for a duration proportional to the duty cycle.
 *
 * @param duty The duty cycle percentage (0-100)
 */
void Driver_GPIO_DutyCycle2s(uint32_t duty);

/**
 * @brief Toggle the state of the LED pin
 */
void Driver_GPIO_Toggle();

#endif // DRIVER_GPIO_H

/*******************************************************************************
* EOF
*******************************************************************************/
