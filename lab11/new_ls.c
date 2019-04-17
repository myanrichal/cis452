#include <stdio.h> 
#include <dirent.h>
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>

int main(int argc, char *argv[]) 
{ 
   DIR *dirPtr; 
   struct dirent *entryPtr; 
   struct stat statBuf;

   if (argc < 2) { 
      printf ("Usage: filename required\n"); 
      exit(1); 
   }

   if (stat (argv[1], &statBuf) < 0) { 
      perror ("huh?  there is "); 
      exit(1); 
   }

   dirPtr = opendir (argv[1]);

   printf("Filename\t\tUserID\tGroupID\tSize\tINODE\n");
   while ((entryPtr = readdir (dirPtr))) {
      stat (entryPtr->d_name, &statBuf);
      //name, user and group ID, file inode #
      printf ("%-20s\t%lu\t%u\t%i\t%u\n",
            entryPtr->d_name, statBuf.st_uid, statBuf.st_gid, statBuf.st_size, entryPtr->d_ino);
    }  
   
   closedir (dirPtr);

   
   return 0; 
}