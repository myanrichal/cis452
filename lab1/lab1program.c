#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

int main (){


    struct termios termInfo;
    char buf[100];

    tcgetattr(0, &termInfo);

    printf("Disabling echo.\n");
    printf("Enter secret word/phrase:\n");
    termInfo.c_lflag &= (~ECHO);
    tcsetattr(0, TCSANOW, &termInfo);

    scanf("%s", buf);
    printf("You entered: ");
    printf("%s\n", buf);

    termInfo.c_lflag |= (ECHO);
    tcsetattr(0, TCSANOW, &termInfo);

    printf("\nDefault behavior restored.\n");
    printf("Enter visible word/phrase: \n");
    scanf("%s", buf);
    printf("You entered: ");
    printf("%s\n", buf);

    printf("Have a great day\n");

    return 0;

}
