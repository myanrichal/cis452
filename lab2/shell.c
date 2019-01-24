#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define STR_LEN 512
#define MAX_ARG 10

int main()
{
    char buf[STR_LEN];

    struct rusage time_buffer;

    puts("Welcome to SuperShell(TM)!");
    puts("Enter commands as you would any other shell:");
    printf("[user@machine Home]$");

    fgets(buf, STR_LEN, stdin);
    printf("Command: %s\n", buf);

    //returns first token
    char* token = strtok(buf, " ");
    char* argv[MAX_ARG];
    char* cmd = buf;
    int i = 0;
    pid_t pid, child;
    int status;

    
    while(strcmp(buf, "quit\n") != 0) {

    //token the rest
    while(token != NULL) {
	    argv[i] = token;
	    token = strtok(NULL, " ");
	    i++;
    }
    	 strtok(argv[i-1], "\n");
	 argv[i] = NULL;

	 pid = fork();

	 if(pid == 0) { //child process

	 //execute the command
   	 if (execvp(cmd, argv) < 0) {
       		 perror("exec failed");
       		 exit(1);
   	 }
	 } else if(pid < 0) {
		 //error
		} else { //parent process
			child = wait(&status);
		}
	
	 //compute the cpu and user time and the number of involuntary context switches
	 getrusage(RUSAGE_SELF, &time_buffer); 
         printf("user microseconds:\t%ld\n", time_buffer.ru_utime.tv_usec);
	 printf("cpu microseconds:\t%ld\n", time_buffer.ru_stime.tv_usec);
	 printf("involuntary context switches:\t%ld\n", time_buffer.ru_nivcsw);

	 //print the prompt out and get ready to loop if necessary
	 printf("[user2machine Home]$");
	 fgets(buf, STR_LEN, stdin);
	 printf("Command: %s\n", buf);
         token = strtok(buf, " ");
         i=0;
    }
   return 0;
}

