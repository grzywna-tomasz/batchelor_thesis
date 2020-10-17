MCU = attiny2313a
COMPILE = avr-gcc -Wall -Os -mmcu=$(MCU)

FILE1 = main
FILE2 = led_avr
OUTPUT = main_avr

default: compile clean

compile:
	$(COMPILE) -c $(FILE1).c -o $(FILE1).o
	$(COMPILE) -c $(FILE2).c -o $(FILE2).o
	$(COMPILE) -o $(FILE1).elf $(FILE1).o $(FILE2).o
	avr-objcopy -j .text -j .data -O ihex $(FILE1).elf $(OUTPUT).hex
	
clean:
	rm $(FILE1).o
	rm $(FILE2).o
	rm $(FILE1).elf
























