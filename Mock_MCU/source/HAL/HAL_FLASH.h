#ifndef HAL_HAL_FLASH_H_
#define HAL_HAL_FLASH_H_

#include "DRIVER_FLASH.h"

void Write_to_Flash(const uint8_t* data, const uint8_t* address);
void HAL_Erase_Flash();

#endif /* HAL_HAL_FLASH_H_ */
