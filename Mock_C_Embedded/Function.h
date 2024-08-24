
/*******************************************************************************
* Definitions
*******************************************************************************/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>
#include <string.h>

#define BYTE_COUNT 2
#define BYTE_TYPE 2
#define HEX_BYTE_LENGTH 2
#define TRUE	1
#define FALSE	0



/*******************************************************************************
* Prorotype
*******************************************************************************/

uint8_t HexCharToValue(char c);
uint8_t HexStringToByte(const char* hexStr);
uint8_t check_Hex(const uint8_t* line);
uint8_t Check_Sum(const uint8_t* hexStr);
uint8_t check_Bytecount(const uint8_t* line);
uint8_t check_S(const uint8_t* line);
uint8_t check_Record_Start(const uint8_t* firstLine);

#endif // FUNCTION_H
/*******************************************************************************
* EOF
*******************************************************************************/
