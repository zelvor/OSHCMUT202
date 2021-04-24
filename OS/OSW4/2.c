#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    size_t MB = 1 * 1;
    size_t maxMB = 0;
    void *ptr = NULL;

    do{
        if (ptr != NULL)
        {
            printf("Bytes of memory checked: %zi\n", maxMB);
            memset(ptr, 0, maxMB);
        }
        maxMB += MB;
        ptr = malloc(maxMB);
    }while(ptr != NULL);

    return 0;
}
