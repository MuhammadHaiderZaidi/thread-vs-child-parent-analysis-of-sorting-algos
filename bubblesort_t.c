#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
 #include <sys/time.h>
  

#define SEED  100

int a[500];
n = 500;

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 


void * bubbleSort(void)
{
	int i, j;  
    	for (i = 0; i < n-1; i++)      
   	 for (j = 0; j < n-i-1; j++)  
        if (a[j] > a[j+1])  
            swap(&a[j], &a[j+1]);  	
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

void fillData(int a[], int len) 
{ 

    int i; 
    for (i=0; i<len; i++) 
        a[i] = rand(); 
    return; 
} 


int main()
{
	 srand(time(NULL)); 
    fillData(a, 500); 
	

	srand(SEED);//
    	struct timeval  start,end;//
    	double time_spent;//
	gettimeofday(&start, NULL);//	

	int status;
	pthread_t tid1;
	pthread_create(&tid1,NULL,bubbleSort,NULL);
	pthread_join(tid1,NULL);
	
	gettimeofday(&end, NULL);
  	time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));//
   	printf("\nTime taken for execution: %f seconds\n", time_spent);	
	
	isSorted(a,n);
	return 0;
}
