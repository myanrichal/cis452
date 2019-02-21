#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <signal.h>
  
char *str;
int *turn;  //0 writer turn
            //1 reader1 turn
            //2 reader2 turn
int *flag;   //flag[0] writer
                //flag[1] reader1
                //flag[2] reader2

void shutDownHandler(int);
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key1 = ftok("shmfile",65); 
    // key_t key2 = ftok("shmfile2",65);
    // key_t key3 = ftok("shmfile3",65);

    // shmget returns an identifier in shmid 
    int shmid1 = shmget(key1,4096,0666|IPC_CREAT); 
    // int shmid2 = shmget(key2,4096,0666|IPC_CREAT); 
    // int shmid3 = shmget(key3,4096,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    str = (char*) shmat(shmid1, (void*)0, 0);
    // turn = (int*) shmat(shmid2, (void*)0, 0);
    // flag = (int*) shmat(shmid3, (void*)0, 0);

    do{
        // *(flag+1) = 1; //sets flag[1] to 1
        // *turn = 0;
        // while(*(flag) == 1 && *turn == 0);
    printf("im here\n");
        printf("Data read from memory: %s\n", str);
        // *(flag+1) = 0; //sets flag[1] to 0

    }while(1);



    return 0; 
} 

void shutDownHandler (int sigNum) {
    //detach from shared memory  
    shmdt(str); 
    // shmdt(turn);
    // shmdt(flag);

	printf(" Okay I'm shutting you down.\n");
	exit(0);
}