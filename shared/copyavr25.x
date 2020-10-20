/* Script for -n: mix text and data on same page */
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:25)
MEMORY
{
  text   (rx)   : ORIGIN = 0, LENGTH = 8K
  data   (rw!x) : ORIGIN = 0x800060, LENGTH = 0xffa0
}
SECTIONS
{
  .text   :
  {
    KEEP (*(.init1))
    *(.text)
     *(.text.*)
     _etext = . ;
  }  > text
  .data          :
  {
     __data_start = . ;
     *(.data*)
     _edata = . ;
     __data_end = . ;
  }  > data AT> text
  .bss  ADDR(.data) + SIZEOF (.data)   : AT (ADDR (.bss))
  {
     __bss_start = . ;
    *(COMMON)
     __bss_end = . ;
  }  > data
   __data_load_start = LOADADDR(.data);
   __data_load_end = __data_load_start + SIZEOF(.data);
}
