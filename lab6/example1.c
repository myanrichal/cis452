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

volatile int32_t exit_flag = 0;
sem_t g_Sem;

//TODO find out how to get exit_flag working
//TODO sem_post to release to execute
int main (int argc, char *argv[])
{
   int status;
   long int i, loop, temp, *shmPtr;
   int shmId;
   pid_t pid;

   signal(SIGINT, shutDownHandler);
   
   sem_init(&g_Sem, 1, 0);


    if(argc > 2 || argc <= 0){
	printf("Bad args dummy\n");
        exit(1);
    } else
        loop = atoi(argv[1]);

    printf("# loops: %ld\n", loop);

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
        sem_wait(&g_Sem);
	temp = shmPtr[0];
        shmPtr[0]=shmPtr[1];
        shmPtr[1]=temp;
	exit_flag = 1;
      }
      if (shmdt (shmPtr) < 0) {
        perror ("just can't let go\n");
        exit (1);
      }
      exit(0);
   }
   else
      for (i=0; i<loop; i++) {
        // swap the contents of shmPtr[1] and shmPtr[0]
        sem_wait(&g_Sem);
	temp = shmPtr[1];
        shmPtr[1]=shmPtr[0];
        shmPtr[0]=temp;
	exit_flag = 1;
      }

   wait (&status);
   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

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
