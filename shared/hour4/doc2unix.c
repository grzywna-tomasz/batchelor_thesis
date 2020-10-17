#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int dos2unix(const char *pathname){
	int ch;
	int cr_flag;
	FILE *in = 0;
	
	if (!(in = fopen(pathname, "r"))){
		fprintf(stderr, "cant open input file.\n");
		return 2;
	}
	
	while((ch = fgetc(in)) != EOF){
		if(cr_flag && ch != '\n')
			putchar('\r');
		if(!(cr_flag = ch == '\r'))
			putchar(ch);
	}
	
	fclose(in);
	return 0;
}

