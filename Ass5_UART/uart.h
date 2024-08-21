
#ifndef UART_H_
#define UART_H_

#include "MKE16Z4.h"

#define SystemCoreClock		48000000
#define BaudRate_UART		9600
#define BLUE_LED_PIN		1
#define PCR_MUX_GPIO_Mask	1 << 8

void initLED();
void initUART0();
void UART0_SendChar(uint8_t data);
void UART0_SendString(uint8_t *str);
uint8_t check_receive();

#endif /* UART_H_ */
