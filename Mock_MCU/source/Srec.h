
/*******************************************************************************
* Definitions
*******************************************************************************/

#ifndef SREC_H
#define SREC_H

#include "MKE16Z4.h"
#include <stdint.h>
#include <string.h>

#define BYTE_COUNT 2
#define BYTE_TYPE 2
#define HEX_BYTE_LENGTH 2
#define TRUE	1
#define FALSE	0

extern uint8_t queue[4][255];
extern uint8_t data[250];
extern uint8_t address[8];
/*******************************************************************************
* Prototypes
*******************************************************************************/

uint8_t HexCharToValue(uint8_t c);
uint8_t HexStringToByte(const uint8_t* hexStr);
uint8_t check_Hex(const uint8_t* line);
uint8_t Check_Sum(const uint8_t* hexStr);
uint8_t check_Bytecount(const uint8_t* line);
uint8_t check_S(const uint8_t* line);
uint8_t check_Format(const uint8_t* line);
uint8_t check_Record_Start(const uint8_t* firstLine);
uint8_t check_Terminate(const uint8_t* line,uint8_t queue_index);
void get_Address(const uint8_t* line);
void get_Data(const uint8_t* line);

#endif // SREC_H
/*******************************************************************************
* EOF
*******************************************************************************/
