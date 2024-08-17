/*******************************************************************************
* Includes
*******************************************************************************/
#include "RTC.h"

/*******************************************************************************
* Variables
*******************************************************************************/
unsigned char led_green_on = 1;
unsigned char led_green_off = 2;
unsigned char led_blue_on = 3;
unsigned char led_blue_off = 3;

/*******************************************************************************
* Main function
*******************************************************************************/
int main() {
	uint32_t previous_time_green = 0;	/* tracking time for GREEN LED */
	uint32_t previous_time_blue = 0;	/* tracking time for BLUE LED*/
	uint32_t current_time = 0;			/* the current time */
	uint8_t green_on_flag = 1;			/* state of GREEN LED*/
	uint8_t blue_on_flag = 1;			/* state of BLUE LED*/

	current_time = RTC->TSR;
	previous_time_blue = current_time;
	previous_time_green = current_time;

	initLED();
	initRTC();

	while(1) {
		if (((current_time - previous_time_green) >= led_green_off) && (!green_on_flag)) {
			previous_time_green = current_time;
			FGPIOB->PDOR &= ~(1 << GREEN_LED_PIN);  /* turn on GREEN LED */
			green_on_flag = 1;
		}
		else if (((current_time - previous_time_blue) >= led_blue_off) && (!blue_on_flag)) {
			previous_time_blue = current_time;
			FGPIOD->PDOR &= ~(1 << BLUE_LED_PIN);	/* turn on BLUE LED */
			blue_on_flag = 1;
		}
		else if (((current_time - previous_time_green) >= led_green_on) && (green_on_flag)) {
			previous_time_green = current_time;
			FGPIOB->PDOR |= 1 << GREEN_LED_PIN;		/* turn off GREEN LED */
			green_on_flag = 0;
		}
		else if(((current_time - previous_time_blue) >= led_blue_on) && (blue_on_flag)) {
			previous_time_blue = current_time;		/* turn off BLUE LED */
			FGPIOD->PDOR |= 1 << BLUE_LED_PIN;
			blue_on_flag = 0;
		}
		else {
			current_time = RTC->TSR;
		}
	}
}
/*******************************************************************************
* EOF
*******************************************************************************/
