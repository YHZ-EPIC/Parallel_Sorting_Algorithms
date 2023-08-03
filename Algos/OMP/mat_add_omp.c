#include<stdio.h>

#include<stdlib.h>

#include <omp.h>

int main(int argc, char * argv[]) {
  int A[4][4], B[4][4], C[4][4];
  int i, j;
  int tid;
  printf("Enter the number of elements in to First Matrix\n");
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      scanf("%d", & A[i][j]);
    }
  }
  printf("Enter the number of elements in to Second Matrix\n");
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      scanf("%d", & B[i][j]);
    }
  }
  #pragma omp parallel shared(A, B, C) private(i, j) { //Pragma block Open  

    tid = omp_get_thread_num();
    if (tid == 0) {
      for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 1; j++) {
          C[i][j] = A[i][j] + B[i][j];
        }
      }
    }

    if (tid == 1) {
      for (i = 0; i <= 1; i++) {
        for (j = 2; j <= 3; j++).

        {
          C[i][j] = A[i][j] + B[i][j];
        }
      }
    }

    if (tid == 2) {
      for (i = 2; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
          C[i][j] = A[i][j] + B[i][j];
        }
      }
    }
    if (tid == 3) {
      for (i = 2; i <= 3; i++) {
        for (j = 2; j <= 3; j++) {
          C[i][j] = A[i][j] + B[i][j];
        }
      }
    }
  } //Pragma Block closed 
  for (i = 0; i <= 3; i++) {
    for (j = 0; j <= 3; j++) {
      printf("%d \t", C[i][j]);
    }
    printf("\n");
  }
  return 0;
}