/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef APP_GPIO_H_
#define APP_GPIO_H_

#include "HAL_GPIO.h"

/*******************************************************************************
* Prototypes
*******************************************************************************/
/*
 * @brief: Fade led
 *
 *	Blinking effect with gradual increase in brightness up to the maximum and
 *	then gradual decrease to 0%,with a cycle time of 4s.
 */
void APP_GPIO_Mode1(FGPIO_Type* fgpio, uint8_t pin);

/*
 * @brief: Toggle Led
 *
 * Toggle the LED with a cycle time of 1s (frequency of 1 Hz).
 */
void APP_GPIO_Mode2(FGPIO_Type* fgpio, uint8_t pin);

#endif /* APP_GPIO_H_ */

/*******************************************************************************
* EOF
*******************************************************************************/
