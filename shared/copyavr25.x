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
    *(.init1)
    KEEP (*(.init1))
    *(.text)
    . = ALIGN(2);
     *(.text.*)
    . = ALIGN(2);
     _etext = . ;
  }  > text
  .data          :
  {
     PROVIDE (__data_start = .) ;
    *(.data)
     *(.data*)
    . = ALIGN(2);
     _edata = . ;
     PROVIDE (__data_end = .) ;
  }  > data AT> text
  .bss  ADDR(.data) + SIZEOF (.data)   : AT (ADDR (.bss))
  {
     PROVIDE (__bss_start = .) ;
    *(.bss)
     *(.bss*)
    *(COMMON)
     PROVIDE (__bss_end = .) ;
  }  > data
   __data_load_start = LOADADDR(.data);
   __data_load_end = __data_load_start + SIZEOF(.data);
}
