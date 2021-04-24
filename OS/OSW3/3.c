#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
	pid_t child_pid;
	child_pid = fork () ;

  	if (child_pid == -1) {
	perror ("fork") ;
 	exit(1);
 	}

	if(child_pid == 0) {
	printf("Hello, ");
	fflush(stdout);
	}	
	else {
	sleep(0.001);
	printf("World!\n" ) ;
	fflush(stdout) ;
	}

	return 0;	
}
