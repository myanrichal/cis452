#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    char* argc = "\0";
    argv[0] = "\0";
    int i = 0;
    pid_t pid, wpid;
    int status;

    printf("buf: %s\n", buf);
    printf("token: %s\n", token);

    //token the rest
    while(token != NULL) {
	    printf("%d\t: %s\n", i, token);
	    argv[i] = token;
	    token = strtok(NULL, " ");
	    i++;
    }
	 argv[i] = NULL;
 	 printf("%d\t: %s\n", i, argv[i]);
	
/*
	argv[0] = "ls";
	argv[1] = "-la";
	argv[2] = NULL;
	 printf("%d\t: %s\n", 0, argv[0]);
	 printf("%d\t: %s\n", 1, argv[1]);
	 printf("%d\t: %s\n", 2, argv[2]);
*/


   
   // while(strcmp(buf, "quit\n") != 0) {

   	 puts("Before the exec");
   	 if (execvp(argv[0], argv) == -1) {
       		 perror("exec failed");
       		 exit(1);
   	 }
   	 puts("After the exec");
    //}

   return 1;
}

