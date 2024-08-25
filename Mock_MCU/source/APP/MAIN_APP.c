/*******************************************************************************
* Includes
*******************************************************************************/
#include "MKE16Z4.h"
#include "HAL_QUEUE.h"
#include "HAL_SREC.h"
#include "HAL_UART.h"
#include "HAL_FLASH.h"

/*******************************************************************************
* Variables
*******************************************************************************/



/*******************************************************************************
* Function
*******************************************************************************/


int main () {
	HAL_Init_UART();
	while(1) {
		pop_queue();
		switch(error_check) {
			case ERR_RECORD_START:
				UART0_SendString((uint8_t*)"Error Record Start !\n");
				break;
			case ERR_HEX:
				UART0_SendString((uint8_t*)"Error Check Hex !\n");
				break;
			case ERR_S_TYPE:
				UART0_SendString((uint8_t*)"Error Check S !\n");
				break;
			case ERR_BYTE_COUNT:
				UART0_SendString((uint8_t*)"Error Check ByteCount !\n");
				break;
			case ERR_CHECK_SUM:
				UART0_SendString((uint8_t*)"Error Check Sum !\n");
				break;
			case ERR_TERMINATE:
				UART0_SendString((uint8_t*)"Error Check Terminate !\n");
				break;
			default:
				if(temp_queue[0] !=  '\0'){
					get_Data(temp_queue);
					get_Address(temp_queue);
					UART0_SendString(data);
					UART0_SendString((uint8_t*)"    ");
					UART0_SendString(address);
					//UART0_SendString(temp_queue);
					UART0_SendChar('\n');
					//Flash_hex(data, address);
				}
				break;
		}
		reset_queue();

	}
}
/*******************************************************************************
* EOF
*******************************************************************************/
