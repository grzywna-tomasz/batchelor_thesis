#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define SHOW_PID

int main(int argc, char **argv){
#ifdef SHOW_PID
	pid_t PID;
#endif
	
	(void) argc;
	(void) argv;
	
#ifdef SHOW_PID
	PID = getpid();
	printf("Process ID is %d\n", (int)PID);
#else
	puts("Hello");
#endif
	return 0;
}
