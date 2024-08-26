#ifndef HAL_QUEUE_H_
#define HAL_QUEUE_H_

#include <HAL_SREC.h>

typedef enum {
	ERR_NONE = 0,
	ERR_RECORD_START,
	ERR_S_TYPE,
	ERR_HEX,
	ERR_BYTE_COUNT,
	ERR_CHECK_SUM,
	ERR_TERMINATE,
} error_t;

extern uint8_t queue[4][255];
extern uint8_t temp_queue[255];
extern uint8_t push_index;		/* index of queue that data will be pushed in */
extern uint8_t element_index;	/* index of element in queue */
extern uint8_t pop_index;		/* index of queue being handled then popped out */
extern uint8_t queue_element;	/* number of unhandled queues */
extern error_t error_check;
extern uint8_t first_flag;
extern uint8_t terminate_flag;

void clear(uint8_t queueIndex);
void clear_temp();
void init_queue();
void push_queue(uint8_t data);
void parse_queue(uint8_t* line);
void pop_queue();
void reset_queue();
#endif /* QUEUE_H_ */
