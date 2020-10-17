/* dos_cvrt.c */

static const char rcsid[] = "abcdf";


/* Revision 
bla bla
dodane zby zachowac zgodn ilosc wierszy

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char **argv){
	char *base_name = 0;

/* wiecej bla bla





*/
	if ((base_name = strrchr(argv[0], '/')) !=0)
		base_name++;
	else
		base_name = argv[0];
		
/* ;)



*/
	if (!strcmp(base_name, "unix_cvrt")){
		/* Perform UNIX -> DOS */
		puts("UNIX to DOS conversion");
	}
	else {
		/* DOS -> UNIX*/
		puts("DOS to UNIX conversion");
	}
	return 0;
}
	
	
