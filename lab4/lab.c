#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define STR_LEN 32

void shutDownHandler(int);
void* do_greeting3 (void* arg);
// arguments :  arg is an untyped pointer pointing to a character
// returns :       a pointer to NULL
// side effects:  prints a greeting

// global data for file count
int fileCount = 0;
float cumulativeTime = 0;
pthread_mutex_t lock;

int main()
{
    pthread_t thread1;
    int status;

    // attempt to init mutex, return 1 if error
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    while(1) {

    // malloc the char array for STR_LEN+1 characters
    char* buf = malloc( sizeof(*buf) * ( STR_LEN + 1 ) );

    printf("\nEnter a filename: ");
    fgets(buf, STR_LEN, stdin);
    printf("You entered: %s\n", buf);

// create and start two threads executing the "do_greeting3" function
// pass each thread a pointer to its respective argument
    if ((status = pthread_create (&thread1, NULL,  do_greeting3, buf)) != 0) {
        fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
        exit (1);
    }

    signal(SIGINT, shutDownHandler); // checks for ^C
    }

    return 0;
}

void* do_greeting3 (void* arg)
{
// note the cast of the void pointer to the desired data type
    char *buf = (char *) arg;

    pthread_mutex_lock(&lock); // lock the thread for stopping race condition

// generate random sleep to simulate reading from disk cache / hard drive
    if( rand() % 10 <= 8){
        sleep(1);
	cumulativeTime++;
	printf("\nFile %s accessed from disk cache.\n", buf);
    } else {
        int time = rand() % 4 + 7;
        sleep( time ); // sleep for 7-10 seconds randomly
	cumulativeTime += time;
	printf("\nFile %s accessed from hard drive.\n", buf);
    }

    fileCount++;
    free(buf);

    pthread_mutex_unlock(&lock); // unlock the thread

    return NULL;
}

// this handles the ^C interrupt
// it prints the files serviced
// then it exits gracefully, closing all threads
void shutDownHandler(int signum){
    float avgTime = cumulativeTime / fileCount;
    printf("\nNumber of files accessed: %d\n", fileCount);
    printf("Average access time: %f\n", avgTime);

    pthread_mutex_destroy(&lock); // destroy the mutex

    exit(0);
}

