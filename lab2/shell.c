#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
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
    puts("[user@machine HomeQQ]$");

    fgets(buf, STR_LEN, stdin);
    printf("Command: %s\n", buf);

    //returns first token
    char* token = strtok(buf, " ");
    char* argv[MAX_ARG];
    char* cmd = buf;
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
    	 strtok(argv[i-1], "\n");
	 argv[i] = NULL;
 	 printf("%d\t: %s\n", i, argv[i]);
   
	 //execute the command
   	 if (execvp(cmd, argv) < 0) {
       		 perror("exec failed");
       		 exit(1);
   	 }

	 getrusage(RUSAGE_SELF, &time_buffer);
	 printf("user microseconds: %ld\n", time_buffer.ru_utime.tv_usec);
	 

   	 puts("Finished!");

   return 0;
}

