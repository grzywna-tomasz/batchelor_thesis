#include <string.h>

char*
Basename(char *pathname){
	char *cp = 0;
	
	if (cp = strrchr(pathname, '/'))
		return cp + 1;
	return pathname;
}
