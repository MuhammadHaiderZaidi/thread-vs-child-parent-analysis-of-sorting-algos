#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/time.h>  

#define SEED  100

  
void mergeSort(int a[], int l, int h) 
{ 
    int i, len=(h-l+1); 
  
    if (l<h) 
    { 

    pid_t lpid,rpid; 
    lpid = fork(); 
    if (lpid<0) 
    { 
        perror("Left Child Proc. not created\n"); 
        _exit(-1); 
    } 
    else if (lpid==0) 
    { 
        mergeSort(a,l,l+len/2-1); 
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
            mergeSort(a,l+len/2,h); 
            _exit(0); 
        } 
    } 
  
    int status;
    waitpid(lpid, &status, 0); 
    waitpid(rpid, &status, 0); 

    merge(a, l, l+len/2-1, h); 
} 

} 
  
  
void merge(int a[], int l1, int h1, int h2) 
{ 
    int count=h2-l1+1; 
    int sorted[count]; 
    int i=l1, k=h1+1, m=0; 

    while (i<=h1 && k<=h2) 
    { 
        if (a[i]<a[k]) 
            sorted[m++]=a[i++]; 
        else if (a[k]<a[i]) 
            sorted[m++]=a[k++]; 
        else if (a[i]==a[k]) 
        { 
            sorted[m++]=a[i++]; 
            sorted[m++]=a[k++]; 
        } 
    } 
  
    while (i<=h1) 
        sorted[m++]=a[i++]; 
  
    while (k<=h2) 
        sorted[m++]=a[k++]; 
  
    int arr_count = l1; 
    for (i=0; i<count; i++,l1++) 
        a[l1] = sorted[i]; 
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
  
// Driver code 
int main() 
{ 
    int shmid; 
    key_t key = IPC_PRIVATE; 
    int *shm_array; 
  
  

    int length = 500; 
  
    /* printf("Enter No of elements of Array:"); 
    scanf("%d",&length); */
  
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
    mergeSort(shm_array, 0, length-1); 
  
	gettimeofday(&end, NULL);
    	time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));//
    printf("\nTime taken for execution: %f seconds\n", time_spent);
	
    isSorted(shm_array, length); 
  
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
