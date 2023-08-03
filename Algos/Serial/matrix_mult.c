#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
   int n = 8;
   int first[n][n], second[n][n], result[n][n];
   int i,j,k;

	// srand(time(NULL));
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                first[i][j] = (rand() % n)+1;
                second[i][j] = (rand() % n)+1;
            }
        }
	printf("\n First Matrix \n");
	for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
         printf("%d  ", first[i][j]);
         if (j == n - 1)
            printf("\n");
      }
   }
	printf("\n Second Matrix \n");
   for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
         printf("%d  ", second[i][j]);
         if (j == n - 1)
            printf("\n");
      }
   }

    clock_t start, end;
    double cpu_time_used;

    start = clock();


   // multiply two matrices.              

   // Initializing elements of matrix mult to 0.
   for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
         result[i][j] = 0;
      }
   }

   // Multiplying first and second matrices and storing it in result
   for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
         for (k = 0; k < n; ++k) {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }

    end = clock();
	
   // display the result
   
     printf("\nOutput Matrix:\n");
   for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
         printf("%d  ", result[i][j]);
         if (j == n - 1)
            printf("\n");
      }
   }

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n\n --> Total Time taken : %f seconds \n\n", cpu_time_used);

   return 0;
}
