#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

void main (){


    struct termios termInfo, save;
    int c;


    c = tcgetattr(0,&termInfo);


    if(c == -1 ){
	    perror("tcgetattr");
	    exit(1);
    }
    if(termInfo.c_lflag & ECHO){
	    printf("Echo is on for you, will turn it off! \n");
	    termInfo.c_lflag &= (~ECHO);
	    printf("Echo has been turned off! \n");
    }else{
	    printf("Echo is off for you, will turn it on! \n");
	    termInfo.c_lflag |= ECHO;
	    printf("Echo has been turned on! \n");
    }

	tcsetattr(0, TCSANOW, &termInfo);

}
