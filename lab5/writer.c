#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h> 
#include <stdlib.h>
#include <signal.h>

#define STR_LEN 64

char *str;
int *turn;
int *flag;
int shmid1, shmid2, shmid3;

void shutDownHandler(int);
  
int main() 
{ 

    signal(SIGINT, shutDownHandler);

    // ftok to generate unique key 
    key_t key1 = ftok("shmfile1",65); 
    // key_t key2 = ftok("shmfile2",65);
    // key_t key3 = ftok("shmfile3",65);

  
    // shmget returns an identifier in shmid 
    int shmid1 = shmget(key1,1024, 0666|IPC_CREAT); 
    // int shmid2 = shmget(key2,1024, 0666|IPC_CREAT); 
    // int shmid3 = shmget(key3,1024, 0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    str = (char*) shmat(shmid1, (void*)0,0);
    // turn = (int*) shmat(shmid2, (void*)0,0);
    // flag = (int*) shmat(shmid3, (void*)0,0);

    // *(flag) = 0;
    // *(flag+1) = 0;
    // *turn = 1;
    // printf("\nFlag:\n%d\t%d\n", *(flag), *(flag+1));
    // printf("Turn:\n%d\n", *turn);


    do{
        // *(flag) = 1; //sets flag[0] to 1
        // *turn = 1;
        // while(*(flag+1) == 1 && *turn == 1);
        printf("\nWrite Data:  ");
        fgets(str, STR_LEN, stdin);
        printf("Data written in memory: %s\n",str);
        // *(flag) = 0; //sets flag[0] to 0
    }while(1);
      

  
    return 0; 
} 

void shutDownHandler (int sigNum) {
    //detach from shared memory  
    shmdt(str);
    // shmdt(turn);
    // shmdt(flag);
    // // destroy the shared memory 
    shmctl(shmid1,IPC_RMID,NULL); 
    // shmctl(shmid2,IPC_RMID,NULL);
    // shmctl(shmid3,IPC_RMID,NULL);

	printf(" Okay I'm shutting you down.\n");
	exit(0);
}