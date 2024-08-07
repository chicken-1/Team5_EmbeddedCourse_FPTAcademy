#include "GPIO.h"

void mode1() {
    uint32_t count_ms = 0;
    uint32_t duty;
    while(count_ms < 8) {

        for(duty = 1; duty <= 100; duty++) {
            duty_cycle_2s(duty);
        }

        for(duty = 100; duty > 0; duty--) {
            duty_cycle_2s(duty);
        }

        count_ms += 4;
    }
}

void mode2() {
    uint32_t count_ms = 0;
    while(count_ms < 8) {
        FGPIOB->PTOR |= GREEN_LED_PIN;
        delay_1s();
        count_ms++;
    }
}

int main() {
    initLed();
    while(1){
        mode1();
        mode2();
    }
}
