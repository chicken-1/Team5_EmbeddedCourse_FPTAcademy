#ifndef HAL_HAL_FLASH_H_
#define HAL_HAL_FLASH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "DRIVER_FLASH.h"  /* Include the Flash driver header */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief  Writes data to the specified address in Flash memory.
 *
 * @param  data: Pointer to the data to be written to Flash memory.
 *               This data is typically raw byte data.
 * @param  address: Pointer to the address in Flash memory where the data
 *                  should be written.
 *
 * @note   Ensure the Flash memory region is erased before writing new data.
 *         This function may handle alignment and size restrictions of the Flash memory.
 */
void Write_to_Flash(const uint8_t* data, const uint8_t* address);

/**
 * @brief  Erases the Flash memory.
 *
 * @note   This function typically erases a specific sector or region of the Flash memory,
 *         depending on the implementation in the Flash driver.
 */
void HAL_Erase_Flash(void);

#endif /* HAL_HAL_FLASH_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
