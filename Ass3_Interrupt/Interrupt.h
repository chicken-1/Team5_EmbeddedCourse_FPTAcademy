/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "MKE16Z4.h"

/*******************************************************************************
* Enumerations
*******************************************************************************/
/**
 * @brief Enum for defining the LED modes.
 */
typedef enum {
    MODE1,       /**< Mode 1: Turn on the LED. */
    MODE2,       /**< Mode 2: Blink the LED at 5Hz using the SysTick timer. */
    MODE3,       /**< Mode 3: Gradually brighten the LED over a 4-second cycle using the SysTick timer. */
    STOP_MODE,   /**< STOP_MODE: Stop all LED activities. */
} mode;

/*******************************************************************************
* Prototypes
*******************************************************************************/

/**
 * @brief Initialize the GREEN LED for operation.
 *
 * This function sets up the necessary hardware configurations to control
 * the GREEN LED, including setting the appropriate GPIO pins and modes.
 */
void Init_GREEN_LED();

/**
 * @brief Initialize SW3 button for interrupts.
 *
 * This function configures the SW3 button to generate interrupts when pressed,
 * enabling the system to switch between LED modes based on button presses.
 */
void InitSW3();

/**
 * @brief Execute the operations for MODE1.
 *
 * This function is called when the LED is in MODE1. It turns on the LED
 * continuously without blinking or dimming.
 */
void mode1();

/**
 * @brief Execute the operations for MODE2.
 *
 * This function is called when the LED is in MODE2. It blinks the LED at
 * a frequency of 5Hz using the SysTick timer.
 */
void mode2();

/**
 * @brief Execute the operations for MODE3.
 *
 * This function is called when the LED is in MODE3. It gradually increases
 * the brightness of the LED from 0% to 100% over a period of 4 seconds.
 */
void mode3();

/**
 * @brief Execute operations for STOP_MODE.
 *
 * This function is called to stop all LED activities, effectively turning
 * off the LED and ceasing any blinking or brightness adjustment.
 */
void stop_mode();

#endif /* INTERRUPT_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
