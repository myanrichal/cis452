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

    printf("hello we are working today");

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
        signal(SIGUSR1, catchSignal);
    }
}


void catchSignal(int sigIn) {
    if (sigIn == SIGUSR1){
        printf("Received SIGUSR1!\n");
    } else if (sigIn == SIGUSR2) {
        printf("Recieved SIGUSR2!\n");
    }
}


/*** 
 * 
    write a parent program that:
        spawns off a child process
        installs signal handler(s) for the two user-defined signals (SIGUSR1/SIGUSR2)
        when a user-defined signal is received, it reports the type of signal sent
            note: it may be necessary to reinstall your signal handler after a signal is received
        terminates gracefully upon receiving a Control-C
    the child process should repeatedly:
        wait a random amount of time (e.g. one to five seconds)
        randomly send one of the two user-defined signals to its parent


TODO: 
        verify these things: 
            fork is working
            random signal is sent at random delay by child
        
        do these things: 
            setup SIGUSR1/2  (user defined signals) 
            catch the sent signal
*/