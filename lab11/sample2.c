#include <stdio.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>

int main() 
{ 
   DIR *dirPtr; 
   struct dirent *entryPtr; 
   struct stat statBuf;

   dirPtr = opendir (".");

   printf("Filename\tRecord Length\tFile Size\n");
   while ((entryPtr = readdir (dirPtr))) {
      stat (entryPtr->d_name, &statBuf);
      printf ("%-20s\t%lu\t%u\n", entryPtr->d_name, entryPtr->d_reclen, statBuf.st_size);
    }  
   closedir (dirPtr); 
   return 0; 
}