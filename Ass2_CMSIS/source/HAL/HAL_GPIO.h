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
<<<<<<< HEAD:Assg2_CMSIS/source/DRIVER/Driver_GPIO.h
//void Driver_GPIO_InitLed();
=======
void HAL_GPIO_Init(FGPIO_Type* fgpio, uint8_t pin);
>>>>>>> 1bbfb703fcc526d442c99aba4d39df4ad0da6988:Ass2_CMSIS/source/HAL/HAL_GPIO.h

/**
 * @brief Delay for approximately 200 microseconds
 *
 * This function creates a delay of approximately 200 microseconds
 * by running a loop with NOP instructions.
 */
<<<<<<< HEAD:Assg2_CMSIS/source/DRIVER/Driver_GPIO.h

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
=======
void HAL_GPIO_Delay200us();
>>>>>>> 1bbfb703fcc526d442c99aba4d39df4ad0da6988:Ass2_CMSIS/source/HAL/HAL_GPIO.h

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
<<<<<<< HEAD:Assg2_CMSIS/source/DRIVER/Driver_GPIO.h
//void Driver_GPIO_DutyCycle2s(uint32_t duty);

#endif // DRIVER_GPIO_H
=======
void HAL_GPIO_Set_DutyCycle2s(uint32_t duty, FGPIO_Type* fgpio, uint8_t pin);

#endif // HAL_GPIO_H
>>>>>>> 1bbfb703fcc526d442c99aba4d39df4ad0da6988:Ass2_CMSIS/source/HAL/HAL_GPIO.h

/*******************************************************************************
* EOF
*******************************************************************************/
