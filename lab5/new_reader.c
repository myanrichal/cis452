
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>

#define READER 1
#define WRITER 0

void shutDownHandler(int);

char *str;
int *flag, shmid, shmid2;
  
int main() 
{ 

    signal(SIGINT, shutDownHandler);

    // ftok to generate unique key 
    key_t key = ftok("/home/vredevch/cis452/lab5/example1.c", 123456);
    key_t flagkey = ftok("/home/vredevch/cis452/lab5/new_reader.c", 123456);
    // shmget returns an identifier in shmid 
    shmid = shmget(key, 4096, IPC_CREAT|S_IRUSR|S_IWUSR); 
    shmid2 = shmget(flagkey, 4096, IPC_CREAT|S_IRUSR|S_IWUSR);
  
    // shmat to attach to shared memory 
    str = (char*) shmat(shmid,(void*)0,0); 
    flag = (int*) shmat(shmid2, NULL, 0);
    
  
    while(1){
        while(*flag == 1);

        printf("Data read from memory: %s\n", str); 

        *flag = 1;
    }
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 

void shutDownHandler (int sigNum) {
    //detach from shared memory  
    shmdt(str); 
    shmdt(flag);

    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid2, IPC_RMID, NULL);

	printf("\nClean shutdown. Shared memory detached and destroyed.\n");

	exit(0);
}
