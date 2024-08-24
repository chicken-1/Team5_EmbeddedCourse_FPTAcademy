
/*******************************************************************************
* Definitions
*******************************************************************************/

#ifndef SREC_H
#define SREC_H

#include "MKE16Z4.h"
#include <stdint.h>
#include <string.h>

#define BC_FIELD_LENGTH		2	/* the number of char in byte count field */
#define STYPE_FIELD_LENGTH	2	/* the number of char in S type field */
#define CS_FIELD_LENGTH		2	/* the number of char in check sum field */
#define BYTE_LENGTH			2	/* the number of char in 1 byte */
#define TRUE				1
#define FALSE				0

typedef enum {
	ERR_NONE,
	ERR_RECORD_START,
	ERR_S_TYPE,
	ERR_HEX,
	ERR_BYTE_COUNT,
	ERR_CHECK_SUM,
	ERR_DATA_RECORD,
	ERR_TERMINATE,
} error_t;

extern uint8_t queue[4][256];
extern uint8_t data[250];
extern uint8_t address[8];
/*******************************************************************************
* Prototypes
*******************************************************************************/

uint8_t HexCharToValue(uint8_t c);
uint8_t HexStringToByte(const uint8_t* hexStr);
uint8_t check_Hex(const uint8_t* line);
uint8_t check_Sum(const uint8_t* hexStr);
uint8_t check_Bytecount(const uint8_t* line);
uint8_t check_S(const uint8_t* line);
uint8_t find_data_type(const uint8_t* line);
uint8_t check_Record_Start(const uint8_t* firstLine);
uint8_t check_Terminate(const uint8_t* line);
void get_Address(const uint8_t* line);
void get_Data(const uint8_t* line);

#endif // SREC_H
/*******************************************************************************
* EOF
*******************************************************************************/
