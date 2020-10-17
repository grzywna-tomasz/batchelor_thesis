#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int unix2dos(const char *pathname){
	int ch;
	FILE *in = 0;
	
	if (!(in = fopen(pathname, "r"))){
		fprintf(stderr, "cant open input file.\n");
		return 2;
	}
	
	while((ch = fgetc(in)) != EOF){
		if(ch == '\n')
			putchar('\r');
		putchar(ch);
	}
	
	fclose(in);
	return 0;
}
