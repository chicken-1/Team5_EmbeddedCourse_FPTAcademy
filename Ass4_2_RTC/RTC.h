/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef RTC_H_
#define RTC_H_

#include "MKE16Z4.h"

#define GREEN_LED_PIN			4
#define BLUE_LED_PIN			1
#define PCR_MUX_GPIO_Mask		1 << 8

/*******************************************************************************
* Prototypes
*******************************************************************************/
/**
 * @brief Initialize the LED for operation.
 *
 * This function sets up the necessary hardware configurations to control
 * the GREEN & BLUE LED, including setting the appropriate GPIO pins and modes.
 */
void initLED();

/**
* @brief: This function sets up RTC module initialization with 1kHz clock source
*/
void initRTC();

#endif /* RTC_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
