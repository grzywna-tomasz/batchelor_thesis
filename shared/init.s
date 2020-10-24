#include <avr/io.h>
.section .init,"ax"

.extern _etext
.extern __data_start
.extern __data_end
.extern __bss_start
.extern __bss_end

.extern main


; clear __zero_reg__, load SP
Set_SP__clear_zero_reg:
clr		r1
out		0x3F,	r1
ldi		r28,	0xDF
out		0x3D,	r28

; load .data (RAM) from flash 
copy_data:
ldi	r30, lo8(_etext)
ldi	r31, hi8(_etext)
ldi	r26, lo8(__data_start)
ldi	r27, hi8(__data_start)
ldi	r24, lo8(__data_end)
ldi	r25, hi8(__data_end)
; Compare __data_start __data_end (in case of no data)
cp		r24, r26
cpc	r25, r27
breq	bss_clean
; Load .data from flash to RAM
data_copy_loop:
lpm	r0, z+
st		x+, r0
cp		r24, r26
cpc	r25, r27
brne	data_copy_loop

; Clean RAM for uninitialized data (bss)
bss_clean:
ldi	r26, lo8(__bss_start)
ldi	r27, hi8(__bss_start)
ldi	r24, lo8(__bss_end)
ldi	r25, hi8(__bss_end)
; Compare __bss_start __bss_end (in case of no bss data)
cp	r24, r26
cpc	r25, r27
breq Call_main
; Load "0" into RAM for lengh: __bss_end - __bss_start
bss_clear_loop:
st	x+, r1
cp	r24, r26
cpc	r25, r27
brne	bss_clear_loop
	
; Last init instruction - jump to main
Call_main:
rjmp main
