#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>

#define SIZE 16
#define STR_LEN 3

void shutDownHandler(int);

sem_t *semaphore;

int main (int argc, char *argv[])
{
   int status;
   long int i, loop, temp, *shmPtr;
   int shmid, *count, dummy;
   pid_t pid;
   key_t key = ftok("/home/vredevch/cis452/lab6/example1.c", 123456);


   signal(SIGINT, shutDownHandler);
   
   shmid = shmget(key, 4096, IPC_CREAT|S_IRUSR|S_IWUSR);
   
   semaphore = (sem_t*) shmat(shmid, 0, 0);

   sem_init(semaphore, 1, 1);

    while(1) {
        sem_post(semaphore);
        if( sem_getvalue(semaphore, count) < 0) {
            printf("Something bad happened\n");
        }
        printf("semval: %d\n", count);
        fflush(stdout);
        if(count == 0)
            printf("inside if\n");
    }

   shmdt(semaphore);
   shmctl(shmid, IPC_RMID, 0);

   return 0;
}

void shutDownHandler(int sigNum) {
	
    printf("\nShutting you down\n");
    exit(0);
}
