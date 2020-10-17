/* Default linker script, for normal executables */
/* Copyright (C) 2014-2015 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */
OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:25)
__TEXT_REGION_ORIGIN__ = DEFINED(__TEXT_REGION_ORIGIN__) ? __TEXT_REGION_ORIGIN__ : 0;
__DATA_REGION_ORIGIN__ = DEFINED(__DATA_REGION_ORIGIN__) ? __DATA_REGION_ORIGIN__ : 0x800060;
__TEXT_REGION_LENGTH__ = DEFINED(__TEXT_REGION_LENGTH__) ? __TEXT_REGION_LENGTH__ : 8K;
__DATA_REGION_LENGTH__ = DEFINED(__DATA_REGION_LENGTH__) ? __DATA_REGION_LENGTH__ : 0xffa0;
MEMORY
{
  text   (rx)   : ORIGIN = __TEXT_REGION_ORIGIN__, LENGTH = __TEXT_REGION_LENGTH__
  data   (rw!x) : ORIGIN = __DATA_REGION_ORIGIN__, LENGTH = __DATA_REGION_LENGTH__
}
SECTIONS
{
  .text   :
  {
    *(.vectors)
    KEEP(*(.vectors))
    . = ALIGN(2);
     __ctors_start = . ;
     *(.ctors)
     __ctors_end = . ;
    KEEP(SORT(*)(.ctors))
    *(.init0)  /* Start here after reset.  */
    KEEP (*(.init0))
    *(.init2)  /* Clear __zero_reg__, set up stack pointer.  */
    KEEP (*(.init2))
    *(.init4)  /* Initialize data and BSS.  */
    KEEP (*(.init4))
    *(.init9)  /* Call main().  */
    KEEP (*(.init9))
    *(.text)
    . = ALIGN(2);
     *(.text.*)
    . = ALIGN(2);
    *(.fini9)  /* _exit() starts here.  */
    KEEP (*(.fini9))
    *(.fini0)  /* Infinite loop after program termination.  */
    KEEP (*(.fini0))
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
  /* Global data not cleared after reset.  */
  
}