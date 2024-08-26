/*******************************************************************************
 * @file        HAL_SREC.h
 * @brief       Header file for S-Record handling functions for MKE16Z4 microcontroller
 * @version     1.0
 * @date        2024-08-26
 ******************************************************************************/

#ifndef HAL_SREC_H
#define HAL_SREC_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "MKE16Z4.h"       /* Include microcontroller-specific definitions */
#include <stdint.h>        /* Standard integer types */
#include <string.h>        /* String handling functions */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BYTE_COUNT        2         /* Number of bytes for byte count field */
#define BYTE_TYPE         2         /* Number of bytes for record type field */
#define HEX_BYTE_LENGTH   2         /* Length of a single hex byte (2 characters) */
#define TRUE              1         /* Boolean TRUE value */
#define FALSE             0         /* Boolean FALSE value */

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern uint8_t queue[4][255];      /* Queue to store data for processing */
extern uint8_t data[255];          /* Data array to store extracted data */
extern uint8_t address[8];         /* Address array to store extracted addresses */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief  Converts a hexadecimal character to its corresponding value.
 *
 * @param  c: Hexadecimal character (0-9, A-F, a-f).
 *
 * @return Returns the value of the hex character as an 8-bit unsigned integer.
 *         If the character is invalid, the return value may be undefined.
 */
uint8_t HexCharToValue(uint8_t c);

/**
 * @brief  Converts a hexadecimal string to a byte.
 *
 * @param  hexStr: Pointer to the hexadecimal string (2 characters).
 *
 * @return Returns the corresponding byte value as an 8-bit unsigned integer.
 */
uint8_t HexStringToByte(const uint8_t* hexStr);

/**
 * @brief  Checks if the given string contains valid hexadecimal characters.
 *
 * @param  line: Pointer to the string to be checked.
 *
 * @return Returns TRUE if the string is valid hexadecimal, otherwise FALSE.
 */
uint8_t check_Hex(const uint8_t* line);

/**
 * @brief  Calculates the checksum of a given hexadecimal string.
 *
 * @param  hexStr: Pointer to the hexadecimal string.
 *
 * @return Returns the calculated checksum as an 8-bit unsigned integer.
 */
uint8_t Check_Sum(const uint8_t* hexStr);

/**
 * @brief  Validates the byte count field of an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if the byte count is valid, otherwise FALSE.
 */
uint8_t check_Bytecount(const uint8_t* line);

/**
 * @brief  Checks the type of S-record by examining the record type field.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns the record type as an 8-bit unsigned integer.
 */
uint8_t check_S(const uint8_t* line);

/**
 * @brief  Validates the format of an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if the format is correct, otherwise FALSE.
 */
uint8_t check_Format(const uint8_t* line);

/**
 * @brief  Checks if the line is the start of an S-record sequence.
 *
 * @param  firstLine: Pointer to the first line of the S-record.
 *
 * @return Returns TRUE if it is the start of a sequence, otherwise FALSE.
 */
uint8_t check_Record_Start(const uint8_t* firstLine);

/**
 * @brief  Checks if the line is a termination record.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @return Returns TRUE if it is a termination record, otherwise FALSE.
 */
uint8_t check_Terminate(const uint8_t* line);

/**
 * @brief  Extracts the address from an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @note   The extracted address is stored in the global `address` array.
 */
void get_Address(const uint8_t* line);

/**
 * @brief  Extracts the data from an S-record line.
 *
 * @param  line: Pointer to the S-record line.
 *
 * @note   The extracted data is stored in the global `data` array.
 */
void get_Data(const uint8_t* line);

#endif /* HAL_SREC_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
