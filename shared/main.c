#include <avr/io.h>

char char_init = 32;

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

void Delay(unsigned int iDelayValue) {
	volatile unsigned long ulDelayCounter = 300;
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
