#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main() {
    long sz = getpagesize();
    printf("%ld\n", sz);

    struct timespec t;
    clock_getres(CLOCK_MONOTONIC, &t);
    
    printf("%ldns\n", t.tv_nsec);


}