/*******************************************************************************
* Include
*******************************************************************************/
#include "HAL_QUEUE.h"

/*******************************************************************************
* Variables
*******************************************************************************/

uint8_t queue[4][255];
uint8_t temp_queue[255];
uint8_t push_index = 0;
uint8_t element_index = 0;
uint8_t pop_index = 0;
uint8_t queue_element = 0;
error_t error_check = ERR_NONE;
uint8_t first_flag = 0;
uint8_t terminate_flag = 0;

/*******************************************************************************
* Function
*******************************************************************************/

void clear(uint8_t index){
	uint8_t j = 0;

	while(queue[index][j] != '\0'){
		queue[index][j] = '\0';
		j++;
	}
}

void clear_temp() {
	uint8_t index = 0;

	while(temp_queue[index] != '\0') {
		temp_queue[index] = '\0';
		index++;
	}
}

void init_queue(){
	for(int i =0; i < 4; i++){
		clear(i);
	}
}

void push_queue(uint8_t data){
	if(data == '\n'){
		push_index++;
		queue_element++;

		if(push_index == 4){
			push_index = 0;
		}
		//clear(push_index);
		element_index = 0;

	}else if(data == '\r'){
		/*do nothing*/
	}else{
		queue[push_index][element_index] = data;
		element_index++;
	}
}


void parse_queue(uint8_t* line){
	if(first_flag == 0){
		if(!check_Record_Start(line)){
			error_check = ERR_RECORD_START;
		}
		first_flag = 1;
	}

	if(!check_Hex(line)) {
		error_check = ERR_HEX;
	}

	if(!check_S(line)) {
		error_check = ERR_S_TYPE;
	}

	if(!check_Bytecount(line)) {
		error_check = ERR_BYTE_COUNT;
	}

	if(!Check_Sum(line)) {
		error_check = ERR_CHECK_SUM;
	}
	if(!check_Terminate(line)) {
			error_check = ERR_TERMINATE;
	}

}

void pop_queue(){
	if(queue_element > 0){
		strcpy((char*)temp_queue, (char*)queue[pop_index]);

		parse_queue(queue[pop_index]);
		queue_element--;

		if((queue[pop_index][1] == '9') || (queue[pop_index][1] == '8') || (queue[pop_index][1] == '7')){
							terminate_flag = 1;
							first_flag = 0;
						}


		clear(pop_index);
		pop_index++;

		if(pop_index == 4){
			pop_index = 0;
		}
	}
}

void reset_queue(){
	error_check = ERR_NONE;
			clear_temp();

			if(terminate_flag == 1){
				init_queue();
				terminate_flag = 0;
				push_index = 0;
				pop_index = 0;
			}
}
/*******************************************************************************
* EOF
*******************************************************************************/
