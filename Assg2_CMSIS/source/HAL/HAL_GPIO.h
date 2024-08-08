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
void HAL_GPIO_InitLed();

/*
 * @brief: Fade led
 *
 *	Blinking effect with gradual increase in brightness up to the maximum and
 *	then gradual decrease to 0%,with a cycle time of 4s.
 */
void HAL_GPIO_Mode1();

/*
 * @brief: Toggle Led
 *
 * Toggle the LED with a cycle time of 1s (frequency of 1 Hz).
 */
void HAL_GPIO_Mode2();

#endif // HAL_GPIO_H

/*******************************************************************************
* EOF
*******************************************************************************/
