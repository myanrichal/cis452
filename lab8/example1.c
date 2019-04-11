#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int g_u1;
int g_u2;
int g_i1 = 1;
int g_i2 = 1;

void myfunc();

int main(int argc, char* argv[])
{
    /* Check direction of heap */
    char *heap1;
    char *heap2;

    heap1 = (char *) malloc(4);
    heap2 = (char *) malloc(4);

    printf("heap1: %p\nheap2: %p\n", &heap1, &heap2);
    printf("g_u1: %p\ng_u2: %p\n", &g_u1, &g_u2);
    printf("g_i1: %p\ng_i2: %p\n", &g_i1, &g_i2);
    printf("arg0: %p\narg1: %p\n", &argv[0], &argv[1]);

    myfunc(1,2);

    return 0;
}

void myfunc(int p1, int p2){
    
    int l1 = 1;
    int l2 = 1;

    printf("l1: %p\nl2: %p\n", &l1, &l2);
    printf("p1: %p\np2: %p\n", &p1, &p2);

    return;
}