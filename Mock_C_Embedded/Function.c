/*******************************************************************************
* Includes
*******************************************************************************/

#include <string.h>
#include "function.h"

/*******************************************************************************
* Function
*******************************************************************************/

uint8_t HexCharToValue(char c) { // ten bien co y nghia
    uint8_t result = 0;

    if ((c >= '0') && (c <= '9')) {
        result = c - '0';
    }
    else if ((c >= 'A') && (c <= 'F')) {
        result = c - 'A' + 10;
    }
    else if ((c >= 'a') && (c <= 'f')) {
        result = c - 'a' + 10;
    }

    return result;
}

uint8_t HexStringToByte(const char* hexStr) {
    uint8_t value = (HexCharToValue(hexStr[0]) << 4) | HexCharToValue(hexStr[1]);
    return value;
}

uint8_t check_Hex(const uint8_t* line) {
	uint8_t e_line = 2;
	uint8_t flag = 1;
	uint8_t check = flag;
	while ((line[e_line] != '\n') && (line[e_line] != '\0')) {
		if ((line[e_line] >= '0') && (line[e_line] <= '9')) {
			flag = 1;
		}
		else if ((line[e_line] >= 'A') && (line[e_line] <= 'F')) {
			flag = 1;
		}
		else {
			flag = 0;
			check = flag;
		}
		e_line++;
	}

	return check;
}

uint8_t Check_Sum(const uint8_t* hexStr) {
    uint8_t checkVal = 0;
    uint8_t size_rc = (uint8_t)strlen(hexStr);
    uint8_t checksum = HexStringToByte(&hexStr[size_rc - 2]);

    uint8_t sum = 0;
    uint8_t index = 0;
    for (index = 2; index < size_rc - 2; index += 2) { //index
        uint8_t count = HexStringToByte(&hexStr[index]);
        sum += count;
    }

    sum = 0xFF - (sum & 0xFF);

    if (sum == checksum) {
        checkVal = 1;
    }
    else {
        checkVal = 0;
    }

    return checkVal;
}

uint8_t check_Bytecount(const uint8_t* line) {
    uint8_t checkVal = 0;

    uint8_t count = HexStringToByte(&line[2]);

    uint32_t size_rc = (uint32_t)strlen(line);

    uint32_t dataLength = size_rc - BYTE_COUNT - BYTE_TYPE;

    if (count == (dataLength / HEX_BYTE_LENGTH)) {
        checkVal = 1;
    }
    else
    {
        checkVal = 0;
    }

    return checkVal;
}

uint8_t check_S(const uint8_t* line) {
	uint8_t flag = TRUE;

	if (line[0] != 'S') {
		flag = FALSE;
	}
	else {
		if (line[1] == '4') {
			flag = FALSE;
		}
		else if ((line[1] < '0') || (line[1]>'9')) {
			flag = FALSE;
		}
		else {
			flag = TRUE;
		}
	}

	return flag;
}

uint8_t check_Format(const uint8_t* line) {
	uint8_t e_line1 = 1;
	uint32_t count_S1 = 0;
	uint32_t count_S2 = 0;
	uint32_t count_S3 = 0;
	uint8_t terminal[1] = "1";
	while ((line) != NULL) {
		if (line[e_line1] == '1') {
			count_S1++;
		}
		else if (line[e_line1] == '2') {
			count_S2++;
		}
		else if (line[e_line1] == '3') {
			count_S3++;
			}
		else{
			/*do nothing*/
		}
	}
	if ((count_S1 > count_S2) && (count_S1 > count_S3)) {
		terminal[0] = '1';
	}
	else if ((count_S2 > count_S1) && (count_S2 > count_S3)) {
		terminal[0] = '2';
	}
	else if ((count_S3 > count_S1) && (count_S3 > count_S2)) {
		terminal[0] = '3';
	}
	else {
		terminal[0] = 'F';
	}
	return terminal[0];

}

uint8_t check_Record_Start(const uint8_t* firstLine) {
	uint8_t flag = TRUE;

	if ((firstLine[0] != 'S') || (firstLine[1] != '0')) {
		flag = FALSE;
	}
	else {
		flag = TRUE;
	}

	return flag;
}

//uint8_t check_Terminate(const uint8_t* line,uint8_t queue_index){
//	uint8_t flag = TRUE;
//	uint8_t data_type = 0;
//	data_type = check_Format(line);
//	if(queue[queue_index++][0] == '\0'){
//		if(data_type == '1' && line[1] == '9' ){
//			flag = TRUE;
//		}else if(data_type == '2' && line[1] == '8'){
//			flag = TRUE;
//		}else if(data_type == '3' && line[1] == '7'){
//			flag = TRUE;
//		}else{
//			flag = FALSE;
//		}
//	}
//
//}



/*******************************************************************************
* EOF
*******************************************************************************/
