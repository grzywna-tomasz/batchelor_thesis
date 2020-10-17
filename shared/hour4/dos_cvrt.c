/* dos_cvrt.c */

static const char rcsid[] = "abcdf";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "dos_cvrt.h"

static char *Basename(const char *path){
	char *base_name = 0;
	
	if ((base_name = strrchr(path, '/')) !=0)
		base_name++;
	else
		base_name = path;
	
	return base_name;
}



int main(int argc, char **argv){
	int rc;
	char *base_name;
	int (*conv)(const char *pathname);
	int index;
	
	base_name = Basename(argv[0]);
	
	if (argc <= 2){
		fprintf(stderr, "missing input file.\n");
		return 1;
	}
		
	if (!strcmp(base_name, "unix_cvrt")){
		conv = unix2dos;
	}
	else {
		conv = dos2unix;
	}
	
	for(index=1; index<argc; index++){
		if ((rc = conv(argv[index])) != 0)
			break;
	}
	
	return rc;
}
	

