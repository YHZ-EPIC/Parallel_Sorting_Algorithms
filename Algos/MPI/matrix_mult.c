#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"

#define N 8

void print_results(char *prompt, int a[N][N]);

int main(int argc, char *argv[])
{
    int i, j, k, rank, size, tag = MPI_ANY_TAG, sum = 0;
    int a[N][N];
    int b[N][N];
    int c[N][N];
    int aa[N],cc[N];
	double start,end; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */	
	start = MPI_Wtime();

	int n = N;
    if(rank == 0)
    {   
        srand(time(NULL));
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                a[i][j] = (rand() % n) + 1;
                b[i][j] = (rand() % n) + 1;
            }
        }

	printf("\n First Matrix \n");
	for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                printf(" %d ", a[i][j]);
            }
		printf("\n");
        }

	printf("\n Second Matrix \n");
	for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                printf(" %d ", b[i][j]);
            }
		printf("\n");
        }
    }
    //scatter rows of first matrix to different processes     
    MPI_Scatter(a, N*N/size, MPI_INT, aa, N*N/size, MPI_INT,0,MPI_COMM_WORLD);

    //broadcast second matrix to all processes
    MPI_Bcast(b, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

          //perform vector multiplication by all processes
          for (i = 0; i < N; i++)
            {
                    for (j = 0; j < N; j++)
                    {
                            sum = sum + aa[j] * b[j][i];                
                    }
                    cc[i] = sum;
                    sum = 0;
            }

    MPI_Gather(cc, N*N/size, MPI_INT, c, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
    MPI_Finalize();
    if (rank == 0) 
	{
		print_results("C = ", c);
    		printf("\n Total Runtime = %f\n", end-start);
	}
}

void print_results(char *prompt, int a[N][N])
{
    int i, j;

    // printf ("\n\n %s \n", prompt);
	printf("\n Final Output \n");
    for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                    printf(" %d	", a[i][j]);
            }
            printf ("\n");
    }
    printf ("\n\n");
}
