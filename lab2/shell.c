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

    printf("buf: %s\n", buf);
    printf("token: %s\n", token);

    //token the rest
    while(token != NULL) {
	    printf("%d\t: %s", i, token);
	    argv[i] = token;
	    token = strtok(NULL, " ");
            printf("\targv: %s\n", argv[i]);
	    i++;
    }

    puts("END");
}

