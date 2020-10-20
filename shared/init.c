#include <avr/io.h>

extern uint8_t _etext;
extern uint8_t __data_start;
extern uint8_t __data_end; 
extern uint8_t __bss_start;
extern uint8_t __bss_end;
extern int main(void); 

void my_init (void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void my_init (void) {
	// clear __zero_reg__, load SP
	asm volatile(
	"clr	r1" "\n\t"
	"out	0x3f, r1"	"\n\t"
	"ldi	r28, 0xDF"	"\n\t"
	"out	0x3d, r28"	"\n\t"
	);
	
	// load .data (RAM) from flash 
	asm volatile(
	// load _etext, __data_start, __data_end
	"mov	r30, %A0"	"\n\t"
	"mov	r31, %B0"	"\n\t"
	"mov	r26, %A1"	"\n\t"
	"mov	r27, %B1"	"\n\t"
	"mov	r24, %A2"	"\n\t"
	"mov	r25, %B2"	"\n\t"
	// Compare __data_start __data_end (in case of no data)
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"breq	load_end"	"\n\t"
	// Load .data from flash to RAM
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
	
	// Clean RAM for uninitialized data (bss)
	asm volatile(
	// Load __bss_start, __bss_end
	"mov	r26, %A0"	"\n\t"
	"mov	r27, %B0"	"\n\t"
	"mov	r24, %A1"	"\n\t"
	"mov	r25, %B1"	"\n\t"
	// Compare __bss_start __bss_end (in case of no bss data)
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"breq	bss_end"	"\n\t"
	// Load "0" into RAM for lengh: __bss_end - __bss_start
	"bss_loop:"			"\n\t"
	"st		x+, r1"		"\n\t"
	"cp		r24, r26"	"\n\t"
	"cpc	r25, r27"	"\n\t"
	"brne	bss_loop"	"\n\t"
	"bss_end:"			"\n\t"
	// Last init instruction - jump to main
	"rjmp main"
	:
	: "r" (&__bss_start), "r" (&__bss_end)
	);
}