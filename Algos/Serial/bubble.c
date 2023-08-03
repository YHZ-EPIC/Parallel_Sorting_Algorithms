// Optimized Bubble sort in C

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// perform the bubble sort
void bubbleSort(int array[], int size) {

  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {
    
    // check if swapping occurs  
    int swapped = 0;
    
    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {
      
      // compare two array elements
      // change > to < to sort in descending order
      if (array[i] > array[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        
        swapped = 1;
      }
    }
    
    // no swapping means the array is already sorted
    // so no need for further comparison
    if (swapped == 0) {
      break;
    }
    
  }
}

// print array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

// main method
int main() {
	int n = 500,i;
  	int *data = malloc(n * sizeof(int));

	printf("\n\n ---- Unsorted Array ---- \n\n");

  	srand(time(NULL));
	for(i=0;i<n;i++)
	{
		data[i] = rand() % n;
		printf(" %d ",data[i]);
		
	}

    clock_t start, end;
    double cpu_time_used;

      start = clock();

  bubbleSort(data, n);
  end = clock();
  printf("\n\n ---- Sorted Array ---- \n\n");
  printArray(data, n);

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("\n\n --> Total Time taken : %f seconds \n\n", cpu_time_used);
}
