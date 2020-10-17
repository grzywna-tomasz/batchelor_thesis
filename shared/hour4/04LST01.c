/* dos_cvrt.c */

static const char rcsid[] = "abcdf";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int 
unix2dos(const char *pathname){
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

int 
dos2unix(const char *pathname){
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


int
main(int argc, char **argv){
	int rc;
	char *base_name;

	if ((base_name = strrchr(argv[0], '/')) !=0)
		base_name++;
	else
		base_name = argv[0];
	
	if (argc != 2){
		fprintf(stderr, "missing input file.\n");
		return 1;
	}
		
	if (!strcmp(base_name, "unix_cvrt")){
		rc = unix2dos(argv[1]);
	}
	else {
		rc = dos2unix(argv[1]);
	}
	
	return rc;
}
	

