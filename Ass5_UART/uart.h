/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef UART_H_
#define UART_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define SystemCoreClock		48000000
#define BaudRate_UART		9600
#define BLUE_LED_PIN		1
#define PCR_MUX_GPIO_Mask	1 << 8

/*******************************************************************************
* variable
*******************************************************************************/
uint8_t check_receive();

/*******************************************************************************
* Prototypes
*******************************************************************************/
/**
 * @brief Initialize the GREEN LED for operation.
 *
 * This function sets up the necessary hardware configurations to control
 * the GREEN & BLUE LED, including setting the appropriate GPIO pins and modes.
 */
void initLED();

/**
 * @brief Initialize UART0 for communication.
 *
 * This function configures UART0 with the specified baud rate and other settings
 * necessary for serial communication. It sets up the UART0 module, enabling it
 * to transmit and receive data.
 */
void initUART0();

/**
 * @brief Send a single character via UART0.
 *
 * This function sends a single byte of data through the UART0 transmit buffer.
 * The function waits until the transmit buffer is empty before sending the data.
 *
 * @param data - The byte of data to be sent.
 */
void UART0_SendChar(uint8_t data);

/**
 * @brief Send a string via UART0.
 *
 * This function sends a null-terminated string through UART0 by transmitting
 * each character one by one. The function continues until the null terminator is reached.
 *
 * @param str - Pointer to the string to be sent.
 */
void UART0_SendString(uint8_t *str);

#endif /* UART_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
