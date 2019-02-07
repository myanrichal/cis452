#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#define STR_LEN 512
#define MAX_ARG 10




int main()
{
    char buf[STR_LEN];

    struct rusage time_buffer;
    struct rusage save_state;
    getrusage(RUSAGE_CHILDREN, &time_buffer);

    puts("Welcome to SuperShell(TM)!");
    puts("Enter commands as you would any other shell:");
    printf("[user@machine Home]$ ");

    fgets(buf, STR_LEN, stdin);
    printf("Command: %s\n", buf);

    //returns first token
    char* token = strtok(buf, " ");
    char* argv[MAX_ARG];
    char* cmd = buf;
    pid_t child, pid;
    int status; 
    int i = 0;

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
		 if (pid == 0) {
			 //child process
			 puts("Before the exec\n");
			 if (execvp(cmd, argv) < 0) {
				 perror("exec failed");
				 exit(1);
			 }
		} else if(pid < 0) {
			// error 
		} else {
			//parent process
			child = wait(&status);
		}

		puts("After the exec\n\n");
		puts("[user@machine HomeQQ]$");
		fgets(buf, STR_LEN, stdin);
		char* cmd = buf;
		printf("Command: %s\n", buf);

    }

   return 0;
}

