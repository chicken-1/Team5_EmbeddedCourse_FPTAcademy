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
 * @brief Enables the clock for a specific GPIO port.
 *
 * @param[in] pcc_port_index Index of the PCC port to enable the clock for
 */
void Driver_GPIO_CLK(uint8_t pcc_port_index);

/**
 * @brief Configure specified pin as a GPIO pin
 *
 * @param[in] port Pointer to the GPIO port
 *             pin Pin number within the port (0-31)
 */
void Driver_GPIO_MUX(PORT_Type* port, uint8_t pin);

/**
 * @brief Configures a GPIO pin as an output.
 *
 * @param[in] fgpio Pointer to the GPIO register structure
 * @param[in] pin Pin number within the GPIO port (0-31)
 */
void Driver_GPIO_Direction_Output(FGPIO_Type* fgpio, uint8_t pin);

/**
 * @brief Resets a GPIO pin low (output 0).
 *
 * @param[in] fgpio Pointer to the GPIO register structure
 * @param[in] pin Pin number within the GPIO port (0-31)
 */
void Driver_GPIO_Output_Reset(FGPIO_Type* fgpio, uint8_t pin);

/**
 * @brief Sets a GPIO pin high (output 1).
 *
 * @param[in] fgpio Pointer to the GPIO register structure
 * @param[in] pin Pin number within the GPIO port (0-31)
 */
void Driver_GPIO_Output_Set(FGPIO_Type* fgpio, uint8_t pin);

/**
 * @brief Toggles a GPIO pin
 *
 * @param[in] fgpio Pointer to the GPIO register structure
 * @param[in] pin Pin number within the GPIO port (0-31)
 */
void Driver_GPIO_Toggle(FGPIO_Type* fgpio, uint8_t pin);

/**
 * @brief Delay for approximately 1 second
 *
 * This function creates a delay of approximately 1 second
 * by running a loop with NOP instructions.
 */
void Driver_GPIO_Delay1s();

#endif // DRIVER_GPIO_H

/*******************************************************************************
* EOF
*******************************************************************************/