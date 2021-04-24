#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_NUMBER_SIZE 100

int main()
{
    FILE *f;
    char buffer[MAX_NUMBER_SIZE];
    pid_t pid;
    int count;
    pid = fork();
    count = 0;
    f = fopen("numbers.txt", "r");
    if (pid == 0){ //Child process div2
        int temp = 0;
        while(fgets(buffer,MAX_NUMBER_SIZE,f)){
            
            temp = atoi(buffer);
            if (temp % 3 == 0)
                count++;
        }
        printf("%d\n",count);
        fclose(f); 
    }
       else if (pid == -1 )
        printf("Fork error!");
    else { //Parent Process div3
        //wait(NULL);
        int temp = 0;
        while(fgets(buffer,MAX_NUMBER_SIZE,f)){
            temp = atoi(buffer);
            if (temp % 2 == 0)
                count++;
        }
        printf("%d\n",count);
        fclose(f);
    }
    return 0;
}
