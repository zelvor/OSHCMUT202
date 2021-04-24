#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pidB, pidC, pidD, pidE, pidF, pidG, pidI;
    printf("A is parent of all. A pid: %d\n", getpid());
    pidB = fork();
    if(pidB == 0){
        printf("\tB pid: %d, its Parent pid: %d\n", getpid(), getppid());
        pidE = fork();

        if(pidE == 0){
            printf("\t\tE pid: %d, its Parent pid: %d\n", getpid(), getppid());
            pidI = fork();

            if(pidI == 0){
                printf("\t\t\tI pid: %d, its Parent pid: %d\n", getpid(), getppid());
 
            }
            else wait(NULL);
        }
        else {
            wait(NULL);
            pidF = fork();
            if(pidF == 0){
                printf("\t\tF pid: %d, its Parent pid: %d\n", getpid(), getppid());
            }
            else wait(NULL);
        }

    }
    else{
        wait(NULL);
        pidC = fork();
        if(pidC == 0){
        printf("\tC pid: %d, its Parent pid: %d\n", getpid(), getppid());
        wait(NULL);
        pidG = fork();
        if(pidG == 0){
            printf("\t\tG pid: %d, its Parent pid: %d\n", getpid(), getppid());
        }
        else wait(NULL);
    }
        else{
        wait(NULL);
        pidD = fork();
        if(pidD == 0){
            printf("\tD pid: %d, its Parent pid: %d\n", getpid(), getppid());
        }
        else wait(NULL);
    }
    }
  
}