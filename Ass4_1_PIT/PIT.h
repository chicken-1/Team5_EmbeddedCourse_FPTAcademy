/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef PIT_H_
#define PIT_H_

#include "MKE16Z4.h"

/*******************************************************************************
* Prototypes
*******************************************************************************/
/**
 * @brief Initialize the GREEN LED for operation.
 *
 * This function sets up the necessary hardware configurations to control
 * the GREEN & BLUE LED, including setting the appropriate GPIO pins and modes.
 */
void initLed();

/**
 * @brief Initialize the PIT for operation.
 *
 * This function sets the hardware configuration for the
 * peripheral interrupt timer (PIT).
 */
void initPIT();

/**
 * @brief Turn on the GREEN LED and turn off the BLUE LED.
 */
void setGreenLed();

/**
 * @brief @brief Turn on the BLUE LED and turn off the GREEN LED
 */
void setBlueLed();

#endif /* PIT_H_ */

/*******************************************************************************
* EOF
*******************************************************************************/
