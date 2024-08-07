#ifndef GPIO_H
#define GPIO_H

#include "MKE16Z4.h"

#define DELAY_CNT_1s            (3750000)
#define DELAY_CNT_200us         ((DELAY_CNT_1s / 10000) * 2) // = 750
#define GREEN_LED_PIN           (1 << 4)

void initLed();
void delay_200us();
void delay_1s();
void duty_cycle_2s(uint32_t duty);

#endif // GPIO_H
