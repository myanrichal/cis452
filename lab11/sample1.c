#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>

int main(int argc, char *argv[]) 
{ 
   struct stat statBuf;

   if (argc < 2) { 
      printf ("Usage: filename required\n"); 
      exit(1); 
   }

   if (stat (argv[1], &statBuf) < 0) { 
      perror ("huh?  there is "); 
      exit(1); 
   }

    if( (statBuf.st_mode & S_IFMT) == S_IFREG ) {
        printf("This FILE has value: %u\n", statBuf.st_mode); 
    } else {
        printf("This DIRECTORY has value: %u\n", statBuf.st_mode);
    }
    printf("Size: %u\n", statBuf.st_size);

   
   return 0; 
}