#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define FOO 4096

int main ()
{
   int shmId;
   char *shmPtr;
   struct shmid_ds buf;
   key_t password = ftok("/usr", 3);

   if ((shmId = shmget (password, FOO, IPC_CREAT+S|S_IRUSR+S|S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
   }
   if ((shmPtr = shmat (shmId, NULL, 0)) == (void*) -1) {
      perror ("can't attach\n");
      exit (1);
   }

   printf ("value a: %p\t value b: %p\n", (void *) shmPtr, (void *) shmPtr + FOO);
   if (shmdt (shmPtr) < 0) {

      perror ("just can't let go\n");
      exit (1);
   }


   if (shmctl(shmId, SHM_STAT, &buf) == -1) {
      perror ("can't deallocate\n");
      exit(1);
   }

   printf("Size of segment: %zu\n", buf.shm_segsz);
   printf("Shared memory ID: %d\n", shmId);

   return 0;
} 