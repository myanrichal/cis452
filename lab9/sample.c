#include <stdio.h>
#include <stdlib.h>

#define COEFFICIENT 59.5
#define KB 1024
#define LOOP 200

int main()
{
   int count, *intPtr;

   long int i, j, dim = COEFFICIENT * KB;

   if ((intPtr = malloc (dim * dim * sizeof(int))) == 0) {   //malloc in virtual memory 
      perror ("totally out of space");
      exit (1);
   }
   for (count=1; count<=LOOP; count++)                 //walk through eery row and column of matrix. touch entire matrix to bring into real memeory. 
   //eseentailly you can forkbomb with this if you malloc a huge size and step through it. 
   //
      for (i=0; i<dim; i++)
         for (j=0; j<dim; j++)
            intPtr[j * dim + i] = (i + j) % count;   //walk through see and otuch all of these element q4
                                                                

   free (intPtr);
   return 0;
}