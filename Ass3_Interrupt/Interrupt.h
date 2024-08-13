/*******************************************************************************
* Definitions
*******************************************************************************/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "MKE16Z4.h"

typedef enum {
	MODE1,
	MODE2,
	MODE3,
	STOP_MODE,
} mode;

/*******************************************************************************
* Prototypes
*******************************************************************************/
void Init_GREEN_LED();
void InitSW3();
void mode1();
void mode2();
void mode3();
void stop_mode();

#endif /* INTERRUPT_H_ */
/*******************************************************************************
* EOF
*******************************************************************************/
