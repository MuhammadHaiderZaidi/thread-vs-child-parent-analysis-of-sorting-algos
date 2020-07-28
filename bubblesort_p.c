#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
  

#define SEED  100

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
        int pid;
        int n, i, j, temp;
        int num[500];
        n = 500;
        

	srand(time(NULL)); 
    	fillData(num, 500); 
	

	srand(SEED);//
    	struct timeval  start,end;//
    	double time_spent;//
	gettimeofday(&start, NULL);//	

        pid = fork();
        if(pid == 0 )
        {
                printf("Child process exucuting\n");
                for(i = 0 ; i < n ; i++ )
                {
                        for(j = 0 ; j < n-i-1 ; j++)
                        {
                                if(num[j] > num[j+1])
                                {
                                        temp = num[j];
                                        num[j] = num[j+1];
                                        num[j+1] = temp;
                                }
                        }
                }

		 gettimeofday(&end, NULL);
  		time_spent = ((double) ((double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec)));//
   		printf("\nTime taken for execution: %f seconds\n", time_spent);
		isSorted(num,n);		
		_exit(0);
		}
	return 0;

}
