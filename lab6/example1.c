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
   int shmId, shmid;
   pid_t pid;
   key_t key = ftok("/home/vredevch/cis452/lab6/example1.c", 123456);


   signal(SIGINT, shutDownHandler);
   
   shmid = shmget(key, 4096, IPC_CREAT|S_IRUSR|S_IWUSR);
   
   semaphore = (sem_t*) shmat(shmid, 0, 0);

   sem_init(semaphore, 1, 1);
 
   loop = atoi(argv[1]);

   if ((shmId = shmget (IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
   }
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) {
      perror ("can't attach\n");
      exit (1);
   }

   shmPtr[0] = 0;
   shmPtr[1] = 1;

   if (!(pid = fork())) {
      for (i=0; i<loop; i++) {
        // swap the contents of shmPtr[0] and shmPtr[1]
        sem_wait(semaphore);
	temp = shmPtr[0];
        shmPtr[0]=shmPtr[1];
        shmPtr[1]=temp;
        sem_post(semaphore);
      }
      if (shmdt (shmPtr) < 0) {
        perror ("just can't let go\n");
        exit (1);
      }
      shmdt(semaphore);
      exit(0);
   }
   else {
      for (i=0; i<loop; i++) {
        // swap the contents of shmPtr[1] and shmPtr[0]
        sem_wait(semaphore);
	temp = shmPtr[1];
        shmPtr[1]=shmPtr[0];
        shmPtr[0]=temp;
        sem_post(semaphore);
      }
   }

   wait (&status);
   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

   shmdt(semaphore);
   shmctl(shmid, IPC_RMID, 0);

   if (shmdt (shmPtr) < 0) {
      perror ("just can't let go\n");
      exit (1);
   }
   if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit(1);
   }

   return 0;
}

void shutDownHandler(int sigNum) {
	
    printf("\nShutting you down\n");
    exit(0);
}
