/* Script for -n: mix text and data on same page */
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:25)
MEMORY
{
  ROM   (rx)   : ORIGIN = 0, LENGTH = 8K
  RAM   (rw!x) : ORIGIN = 0x800060, LENGTH = 0xffa0
}
SECTIONS
{
  .text   :
  {
    KEEP (*(.init))
    *(.text)
     *(.text.*)
     _etext = . ;
  }  > ROM
  .data          :
  {
     __data_start = . ;
     *(.data*)
     _edata = . ;
     __data_end = . ;
  }  > RAM AT> ROM
  .bss  ADDR(.data) + SIZEOF (.data)   : AT (ADDR (.bss))
  {
     __bss_start = . ;
    *(COMMON)
     __bss_end = . ;
  }  > RAM
   __data_load_start = LOADADDR(.data);
   __data_load_end = __data_load_start + SIZEOF(.data);
}
