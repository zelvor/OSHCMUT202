#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ex1.h"

void *aligned_malloc(unsigned int size, unsigned int align)       
{ 
    if(size == 0 || align <= 0){
        return NULL;
    }
    /*Check if align is power of 2 */
    if ((align & (align - 1)) != 0)
    {
        printf("Align must be power of 2 !!");
        return NULL;
    }
    void *ptr;
    void *p = malloc(size + align - 1 + sizeof(void*));

    if(p != NULL){
        ptr = (void*)(((size_t)p + sizeof(void*) + align - 1) & ~(align - 1 ));
        *((void**)((size_t)ptr - sizeof(void*))) = p;
        return ptr;
    }
    return NULL;
}
void *aligned_free(void *ptr)
{ 
    if (!ptr)
        return NULL;
    /*Get the pointer of the block memory*/
    void *block_ptr= *((void**)((size_t)ptr - sizeof(void*))); 
    free(block_ptr);
    return ptr;
}
int main(int argc, char *argv[]){
    printf("Hello!\n");
    printf("program break before calling aligned_malloc : %p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    int *p = (int*)aligned_malloc(sizeof(int) * 4, 8);

}