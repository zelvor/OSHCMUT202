#include <stdio.h>
#include "sum.h"
#include "sub.h"

int main() {    

    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Sum = %d\nSub = %d\n", sum(a,b), sub(a,b));
    
    return 0;
}
