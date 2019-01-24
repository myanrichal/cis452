#include <stdio.h>
#include <sys/types.h>
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

    puts("Welcome to SuperShell(TM)!");
    puts("Enter commands as you would any other shell:");
    puts("[user@machine HomeQQ]$");

    fgets(buf, STR_LEN, stdin);
    printf("Command: %s\n", buf);

    //returns first token
    char* token = strtok(buf, " ");
    char* argv[MAX_ARG];
    char* cmd = buf;
    pid_t child;
    int status; 
    int i = 0;

    //token the rest
    while(token != NULL) {
	    argv[i] = token;
	    token = strtok(NULL, " ");
	    i++;
    }
    	 strtok(argv[i-1], "\n");
	 argv[i] = NULL;
   
    while(strcmp(buf, "quit\n") != 0) {

   	 puts("Before the exec\n");
   	 if (execvp(cmd, argv) < 0) {
       		 perror("exec failed");
       		 exit(1);
   	 }
	 child = wait(&status);
   	 puts("After the exec\n");
    }

   return 0;
}

