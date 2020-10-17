#include <avr/io.h>

extern uint8_t _etext;
extern uint8_t __data_start;
extern uint8_t __data_end;
extern uint8_t __bss_start;
extern uint8_t __bss_end; 

void my_init (void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void my_init (void) {
	// load SP, reset __zer_reg__
	asm volatile(
	"clr	r1" "\n\t"
	"out	0x3f, r1"	"\n\t"
	"ldi	r28, 0xDF"	"\n\t"
	"out	0x3d, r28"	"\n\t"
	);
	
	// load .data (RAM) from flash 
	asm volatile(
	"mov	r30, %A0"	"\n\t"
	"mov	r31, %B0"	"\n\t"
	"mov	r26, %A1"	"\n\t"
	"mov	r27, %B1"	"\n\t"
	"mov	r24, %A2"	"\n\t"
	"mov	r25, %B2"	"\n\t"
	"cp		r30, r26"	"\n\t"
	"cpc	r31, r27"	"\n\t"
	"breq	load_end"	"\n\t"
	
	"load_loop:"		"\n\t" 
	"lpm	r0, z+"		"\n\t"
	"st		x+, r0"		"\n\t"
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"brne	load_loop"	"\n\t"
	"load_end:"			"\n\t"
	:
	: "r" (&_etext), "r" (&__data_start), "r" (&__data_end)
	);
	
	// clear bss
	asm volatile(
	"mov	r26, %A0"	"\n\t"
	"mov	r27, %B0"	"\n\t"
	"mov	r24, %A1"	"\n\t"
	"mov	r25, %B1"	"\n\t"
	
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"breq	bss_end"	"\n\t"
	
	"bss_loop:"			"\n\t"
	"st		x+, r1"		"\n\t"
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"brne	bss_loop"	"\n\t"
	"bss_end:"			"\n\t"
	:
	: "r" (&__bss_start), "r" (&__bss_end)
	);
}