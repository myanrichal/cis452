
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <time.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define MAX 1024

void catchSignal(int);



int main() {
    pid_t pid, parent_pid; 
    srand(time(NULL));
    int r, s;
    parent_pid = getpid(); 

    printf("hello we are working today\n");

    if ((pid = fork()) < 0) {
            perror ("fork failed");
            exit(1);
    } else if(!pid) {
        //child
        while(1) {
            r = rand() % 5 + 1;
            s = rand() % 2;
            sleep(r);
            if(s) {
                kill(parent_pid, SIGUSR1);
            } else {
                kill(parent_pid, SIGUSR2);
            } 
        }
    } else {
    	while(1) {
	    signal(SIGUSR1, catchSignal);
            signal(SIGUSR2, catchSignal);
            printf("waiting....  ");
	    pause();
	}
    }
}


void catchSignal(int sigIn) {
    if (sigIn == SIGUSR1){
        printf("....Received SIGUSR1!\n");
    } else if (sigIn == SIGUSR2) {
        printf("....Recieved SIGUSR2!\n");
    }
}
