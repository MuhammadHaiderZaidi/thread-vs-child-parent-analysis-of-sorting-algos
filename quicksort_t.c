#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>



typedef struct{
	int upperbound;
	int lowerbound;
}PARM;


#define N 500
#define SEED  100

int A[N];
// unsorted data



void fillData(int a[], int len) 
{ 

    int i; 
    for (i=0; i<len; i++) 
        a[i] = rand(); 
    return; 
} 


void isSorted(int arr[], int len) 
{ 
    if (len==1) 
    { 
        printf("Sorting Done Successfully\n"); 
        return; 
    } 
  
    int i; 
    for (i=1; i<len; i++) 
    { 
        if (arr[i]<arr[i-1]) 
        { 
            printf("Sorting Not Done\n"); 
            return; 
        } 
    } 
    printf("Sorting Done Successfully\n"); 
    return; 
} 





void *quicksort(void *aptr)
{
	PARM *ap, aleft, aright;
	int pivot, pivotIndex, left, right, temp;
	int upperbound, lowerbound;
	pthread_t me, leftThread, rightThread;
	me = pthread_self();
	ap = (PARM *)aptr;
	upperbound = ap->upperbound;
	lowerbound = ap->lowerbound;
	pivot = A[upperbound];

	// pick low pivot value
	left = lowerbound - 1;

	// scan index from left side
	right = upperbound;

	// scan index from right side
	if (lowerbound >= upperbound)
		pthread_exit(NULL);
	
	while (left < right) {
	// partition loop
		do { left++;} while (A[left] < pivot);
		do { right--;} while (A[right] > pivot);
		if (left < right ) {

			temp = A[left];
			A[left] = A[right];
			A[right] = temp;
		}
	}
	pivotIndex = left;

	// put pivot back
	temp = A[pivotIndex];
	A[pivotIndex] = pivot;
	A[upperbound] = temp;

	// start the "recursive threads"
	aleft.upperbound = pivotIndex - 1;
	aleft.lowerbound = lowerbound;
	aright.upperbound = upperbound;
	aright.lowerbound = pivotIndex + 1;
	pthread_create(&leftThread, NULL, quicksort, (void *)&aleft);
	pthread_create(&rightThread, NULL, quicksort, (void *)&aright);

	// wait for left and right threads to finish
	pthread_join(leftThread, NULL);
	pthread_join(rightThread, NULL);
}


int main(int argc, char *argv[])
{

	fillData(A,N);	



	srand(SEED);//
    	struct timeval  start,end;//
    	double time_spent;//

	   gettimeofday(&start, NULL);//
	
	clock_t t1, t2; 
  	t1 = clock(); 

	PARM arg;
	int i, *array;
	pthread_t me, thread;
	me = pthread_self();
	arg.upperbound = N-1;
	arg.lowerbound = 0;
	
	pthread_create(&thread, NULL, quicksort, (void *)&arg);
	
	pthread_join(thread, NULL);
	//t1 = clock(); 
	//t2 = clock(); 

	 gettimeofday(&end, NULL);
    	time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));//
    printf("\nTime taken for execution: %f seconds\n", time_spent);
  
 
    // time taken by merge sort in seconds 
    //printf("Time taken: %d\n" , (t2 - t1) );
  	isSorted(A,N);
}
