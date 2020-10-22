#include <avr/io.h>

char char_init = 32;
volatile unsigned long ul_noinit;

void init(void){
	DDRB = 0xF;
	PORTB = 0x4; 
	DDRD = 0xFF;
	PORTD = 0b01000000; 
} 

void set_led(unsigned char ucLedNr){ 
	if(ucLedNr == 0){ 
		//PORTD = 0b00110000;
		PORTD = char_init;
	}
	else{
		PORTD = 0b00000110;
	} 
}

void Delay(unsigned long ulDelayValue) {
	volatile unsigned long ulDelayCounter;
	for (ulDelayCounter= ulDelayValue; ulDelayCounter>0; ulDelayCounter--) {
	}
}

int main(void){
	init();
	ul_noinit = 300000;
	
	while(1){
		Delay(ul_noinit);
		set_led(0);
		Delay(ul_noinit);
		set_led(1);
		ul_noinit = ul_noinit - 3000;
	}
}
