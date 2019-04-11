#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int g_u1;
int g_u2;
int g_i1 = 1;
int g_i2 = 1;



int main(int argc, char *argv[])
{
    // int l1 =2;
    // int l2 =1;
    // int l3 =1;
    // int l4 =1;

    // char *heap1;
    // char *heap2;

    // heap1 = (char *) malloc(15);
    // heap2 = (char *) malloc(15);

    // printf("g_u1: %p\ng_u2: %p\n", &g_u1, &g_u2);
    // printf("g_i1: %p\ng_i2: %p\n", &g_i1, &g_i2);

    printf("st1: %p\nst2: %p\n", &argv[0], &argv[1]);
    // printf("st3: %p\nst4: %p\n", &l3, &l4);

    // printf("heap1: %p\nheap2: %p\n", &heap1, &heap2);


    return 0;
}