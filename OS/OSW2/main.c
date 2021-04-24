#include "findsubstr.h"
#include "readline.h"
#include <stdio.h>
int main(int args, char* argv[]){

	if(args == 1)
	return 1;
	
	char* pattern = argv[1];
	const size_t MAX_LETTERS_PER_LINE = 100;
	
	while(1){
	char str[MAX_LETTERS_PER_LINE];
	int flag = read_line(str);
	if(flag == -1)
	break;
	int idx = find_sub_string(str, pattern);
	if(idx >= 0){
	printf("[%d] %s",flag, str);
	}
}
}
