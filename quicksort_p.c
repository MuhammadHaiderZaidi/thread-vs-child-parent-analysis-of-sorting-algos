#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>  
#include <sys/time.h>  

#define SEED  100


void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 



int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 

        if (arr[j] < pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  

void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 

//
	pid_t lpid,rpid; 
    lpid = fork(); 
    if (lpid<0) 
    { 
        perror("Left Child Proc. not created\n"); 
        _exit(-1); 
    } 
    else if (lpid==0) 
    { 
        quickSort(arr, low, pi - 1); 
        _exit(0); 
    } 
    else
    { 
        rpid = fork(); 
        if (rpid<0) 
        { 
            perror("Right Child Proc. not created\n"); 
            _exit(-1); 
        } 
        else if(rpid==0) 
        { 
             quickSort(arr, pi + 1, high);  
            _exit(0); 
        } 
    }	

	int status;
    waitpid(lpid, &status, 0); 
    waitpid(rpid, &status, 0); 
	 
 } 
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
        a[i] = rand()%200; 
    return; 
} 
  
// Driver code 
int main() 
{ 

    int shmid; 
    key_t key = IPC_PRIVATE; 
    int *shm_array; 
  
	
    int length = 500; 
  
  
    size_t SHM_SIZE = sizeof(int)*length; 
  
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) 
    { 
        perror("shmget"); 
        _exit(1); 
    } 
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1) 
    { 
        perror("shmat"); 
        _exit(1); 
    } 
  
    srand(time(NULL)); 
    fillData(shm_array, length); 
  

	srand(SEED);//
    	struct timeval  start,end;//
    	double time_spent;//
	gettimeofday(&start, NULL);//

    // Sorting 
    quickSort(shm_array, 0, length-1); 
  

	gettimeofday(&end, NULL);
    	time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));//
    printf("\nTime taken for execution: %f seconds\n", time_spent);
	
	isSorted(shm_array,length);
  
    if (shmdt(shm_array) == -1) 
    { 
        perror("shmdt"); 
        _exit(1); 
    } 

    if (shmctl(shmid, IPC_RMID, NULL) == -1) 
    { 
        perror("shmctl"); 
        _exit(1); 
    } 
  
    return 0; 
} 
