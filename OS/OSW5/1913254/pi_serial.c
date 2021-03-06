#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int nPoints = 0;
int count = 0;
time_t    start = 0, end = 0; 

void calPi(){
    srand(time(NULL));
    for(int  i =0 ; i < nPoints; i++){
        double x = (double)rand()/RAND_MAX;
        double y = (double)rand()/RAND_MAX;
        if((x*x) + (y*y) <= 1){
            count++;
        }
    }
}

int main(int argc, char* argv[]){
    clock_t start, end;
    start = clock();
    if(argc != 2){
        printf("Missing nPoints !!");
        return -1;
    }
    nPoints = atoi(argv[1]);

    calPi();
    end = clock();
    double pi = 4*((double)(count)/(double)nPoints);   
    double time_spend = (double)(end-start) / 1000000;
    printf("Pi = %f\nTime serial = %f sec\n",pi,time_spend);
    return 0;
}
