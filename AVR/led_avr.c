#include "led_avr.h"

void init(void){
	DDRB = 0xF;
	PORTB = 0x4;
	DDRD = 0xFF;
	PORTD = 0b01000000;
}

void set_led(unsigned char ucLedNr){
	if(ucLedNr == 0){
		PORTD = 0b00110000;
	}
	else{
		PORTD = 0b00000110;
	}
}
