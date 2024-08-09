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
//void Driver_GPIO_InitLed();

/**
 * @brief Delay for approximately 200 microseconds
 *
 * This function creates a delay of approximately 200 microseconds
 * by running a loop with NOP instructions.
 */

/**
 * @brief Toggle the state of the LED pin
 */

void Driver_GPIO_CLK(uint8_t pcc_port_index);
void Driver_GPIO_MUX(PORT_Type* port, uint8_t pin);
void Driver_GPIO_Direction_Output(FGPIO_Type* fgpio, uint8_t bit);
void Driver_GPIO_Output_OFF(FGPIO_Type* fgpio, uint8_t bit);
void Driver_GPIO_Output_ON(FGPIO_Type* fgpio, uint8_t bit);
void Driver_GPIO_Toggle(FGPIO_Type* fgpio, uint8_t bit);

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
//void Driver_GPIO_DutyCycle2s(uint32_t duty);

#endif // DRIVER_GPIO_H

/*******************************************************************************
* EOF
*******************************************************************************/
