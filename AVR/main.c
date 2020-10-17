#include "led_avr.h"

void Delay(unsigned int iDelayValue) {
	volatile unsigned long ulDelayCounter = 0;
	for (ulDelayCounter=(unsigned long)iDelayValue*300; ulDelayCounter>0; ulDelayCounter--) {
	}
}

int main(void){
	init();
	
    while(1){	
		Delay(1000);
		set_led(0);
		Delay(1000);
		set_led(1);
    }
}
