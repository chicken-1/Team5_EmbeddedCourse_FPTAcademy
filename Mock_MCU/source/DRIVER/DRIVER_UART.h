#ifndef DRIVER_UART_H_
#define DRIVER_UART_H_

#include "MKE16Z4.h"

#define SystemCoreClock		48000000
#define BaudRate_UART		9600

void initUART0();
void UART0_SendChar(uint8_t data);
void UART0_SendString(uint8_t *str);
uint8_t get_Register_Data();
void LPUART0_IRQHandler();

#endif /* DRIVER_UART_H_ */
