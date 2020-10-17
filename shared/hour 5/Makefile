
CC = gcc
OBJS = dos_cvrt.o unix2dos.o dos2unix.o

.c.o:
	$(CC) -c -Wall $(CFLAGS) $<

all: dos_cvrt unix_cvrt

dos_cvrt: $(OBJS)
	$(CC) $(OBJS) -o dos_cvrt
	
unix_cvrt: dos_cvrt
	rm -f unix_cvrt
	ln dos_cvrt
	
clean:
	rm -f *.o core
	
clobber: clean
	rm -f dos_cvrt unix_cvrt
