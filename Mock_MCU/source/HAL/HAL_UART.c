#include "HAL_UART.h"

void HAL_Init_UART(){
	initUART0();
}

void HAL_Sendchar(uint8_t data){
	UART0_SendChar(data);
}

void HAL_SendString(uint8_t* string){
	UART0_SendString(string);
}

uint8_t HAL_get_Register_Data(){
	uint8_t data_reg = 0;
	data_reg = get_Register_Data();
	return data_reg;
}


