#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	int timestamp=0;
	while(1){
	printf("Time: %5d\n", timestamp++);
	sleep(1);
	}
	return 0;
	
}
