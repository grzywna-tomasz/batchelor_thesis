/* dos_cvrt.c */

static const char rcsid[] = "abcdf";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char **argv){
	char *base_name = 0;
	int ch;
	int cr_flag;
	FILE *in = 0;

	if ((base_name = strrchr(argv[0], '/')) !=0)
		base_name++;
	else
		base_name = argv[0];
	
	if (argc != 2){
		fprintf(stderr, "missing input file.\n");
		return 1;
	}
	if (!(in = fopen(argv[1], "r"))){
		fprintf(stderr, "cant open input file.\n");
		return 2;
	}
	
	if (!strcmp(base_name, "unix_cvrt")){
		/* Perform UNIX -> DOS */
		while((ch = fgetc(in)) != EOF){
			if(ch == '\n')
				putchar('\r');
			putchar(ch);
		}
	}
	else {
		/* DOS -> UNIX*/
		cr_flag = 0;
		while((ch = fgetc(in)) != EOF){
			if(cr_flag && ch != '\n')
				putchar('\r');
			if(!(cr_flag = ch == '\r'))
				putchar(ch);
		}
	}
	
	fclose(in);
	
	return 0;
}
	
	
