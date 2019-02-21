
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h> 

#define STR_LEN 1024
#define WRITER 0
#define READER 1

char *str;
int *flag;
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("/home/vredevch/cis452/lab5/example1.c", 123456); 
    key_t flagkey = ftok("/home/vredevch/cis452/lab5/new_reader.c", 123456);
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key, 4096, IPC_CREAT|S_IRUSR|S_IWUSR); 
    int shmid2 = shmget(flagkey, 4096, IPC_CREAT|S_IRUSR|S_IWUSR);
  
    // shmat to attach to shared memory 
    str = (char*) shmat(shmid,(void*)0,0);
    flag = (int*) shmat(shmid2, NULL, 0);
  
    *flag = 1;

    while(1){

        while(*flag == 0);

        printf("Write Data: "); 
        fgets(str, STR_LEN, stdin);  
        printf("Data written in memory: %s\n",str); 

        *flag = 0;
    }
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
} 
