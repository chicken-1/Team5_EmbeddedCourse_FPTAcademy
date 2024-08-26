#ifndef HAL_QUEUE_H_
#define HAL_QUEUE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "HAL_SREC.h"   /* Include the S-Record handling header */

/*******************************************************************************
 * Enumerations
 ******************************************************************************/

/**
 * @brief Enumeration for error codes related to queue processing.
 */
typedef enum {
    ERR_NONE = 0,            /**< No error */
    ERR_RECORD_START,        /**< Error in record start */
    ERR_S_TYPE,              /**< Error in S-record type */
    ERR_HEX,                 /**< Error in hexadecimal format */
    ERR_BYTE_COUNT,          /**< Error in byte count */
    ERR_CHECK_SUM,           /**< Error in checksum */
    ERR_TERMINATE,           /**< Error in termination record */
} error_t;

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern uint8_t queue[4][255];      /**< 2D array representing the main queue */
extern uint8_t temp_queue[255];    /**< Temporary queue for data processing */
extern uint8_t push_index;         /**< Index in queue to push new data */
extern uint8_t element_index;      /**< Index of the current element in queue */
extern uint8_t pop_index;          /**< Index of the queue being processed */
extern uint8_t queue_element;      /**< Number of unhandled queues */
extern error_t error_check;        /**< Variable to store error codes */
extern uint8_t first_flag;         /**< Flag indicating the first queue element */
extern uint8_t terminate_flag;     /**< Flag indicating the presence of a termination record */

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/**
 * @brief Clears the specified queue.
 *
 * @param queueIndex: The index of the queue to be cleared.
 *
 * @note This function sets all elements of the specified queue to zero.
 */
void clear(uint8_t queueIndex);

/**
 * @brief Clears the temporary queue.
 *
 * @note This function sets all elements of the temporary queue to zero.
 */
void clear_temp(void);

/**
 * @brief Initializes the queue system.
 *
 * @note This function sets up all indices and flags to their initial states.
 */
void init_queue(void);

/**
 * @brief Pushes data into the main queue.
 *
 * @param data: The data byte to be pushed into the queue.
 *
 * @note The data is pushed into the queue at the current `push_index`.
 */
void push_queue(uint8_t data);

/**
 * @brief Parses the queue and processes each element.
 *
 * @param line: Pointer to the line being processed from the queue.
 *
 * @note This function is responsible for interpreting the queued data.
 */
void parse_queue(uint8_t* line);

/**
 * @brief Pops the processed queue.
 *
 * @note This function removes the processed queue element and shifts the queue.
 */
void pop_queue(void);

/**
 * @brief Resets the entire queue system.
 *
 * @note This function clears all queues and resets indices and flags.
 */
void reset_queue(void);

#endif /* HAL_QUEUE_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
