#ifndef HAL_HAL_UART_H_
#define HAL_HAL_UART_H_

#include "DRIVER_UART.h"

void HAL_Init_UART();

void HAL_Sendchar(uint8_t data);

void HAL_SendString(uint8_t* string);

uint8_t HAL_get_Register_Data();


#endif /* HAL_HAL_UART_H_ */
