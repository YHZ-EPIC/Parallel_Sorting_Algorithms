#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void bubbleSort(int *arr,int n);

int main(int argc, char** argv) {
	
	/********** Create and populate the array **********/

	// int n = 100;
	int n = 100;
	int c;
	double start,end; 
	int *original_array = malloc(n * sizeof(int));
		
	/********** Initialize MPI **********/
	
	int world_rank;
	int world_size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */	
	start = MPI_Wtime();

	if(world_rank == 0)
{
	srand(time(NULL));
	printf("\n\n This is the unsorted array: \n\n");

	for(c = 0; c < n; c++) {
		
		original_array[c] = rand() % n;
		printf("%d ", original_array[c]);
		
	}

	printf("\n");
	printf("\n");
}

	/********** Divide the array in equal-sized chunks **********/

	int size = n/world_size;
	
	/********** Send each subarray to each process **********/

	int *sub_array = malloc(size * sizeof(int));
	MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Perform the bubbleSort on each process **********/

	bubbleSort(sub_array, size);
	
	/********** Gather the sorted subarrays into one **********/
	int *sorted = NULL;
	if(world_rank == 0) 
	{
		sorted = malloc(n * sizeof(int));
	}
	
	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Make the final bubbleSort call **********/
	if(world_rank == 0) {
		
        	bubbleSort(sorted, (size - 1));
		
		/********** Display the sorted array **********/
		printf("\n\n This is the Sorted array: \n\n");
		for(c = 0; c < n; c++) 
		{			
			printf("%d ", sorted[c]);	
		}
			
		printf("\n");
		printf("\n");
			
		/********** Clean up root **********/
		free(sorted);
			
		}
	
	/********** Clean up rest **********/
	free(original_array);
	free(sub_array);
	
	/********** Finalize MPI **********/
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	MPI_Finalize();
	
	if (world_rank == 0) 
	{
    		printf("\n Total Runtime = %f\n", end-start);
	}
	
}

/********** BubbleSort Function **********/

void bubbleSort(int *array, int size) {

  for (int step = 0; step < size - 1; ++step) {
    int swapped = 0;
    
    for (int i = 0; i < size - step - 1; ++i) {
      if (array[i] > array[i + 1]) {
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        
        swapped = 1;
      }
    }

    if (swapped == 0) {
      break;
    }
    
  }
}
