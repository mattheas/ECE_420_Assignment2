#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

/*
export OMP_NUM_THREADS=3
export OMP_NESTED=TRUE
export OMP_DYNAMIC=FALSE
*/

int thread_cnt = 0;

int fib(int n) {
    if (n<2)
        return n;
    else {
    	int i = 0;
    	int j = 0;
    	#pragma omp parallel
    	{	
    		#pragma omp sections firstprivate(n) reduction(+:i,j)
    		{
    			#pragma omp section
    			{
			i+=fib(n-1);
		        thread_cnt++;
		        } 
		         
			#pragma omp section
			{
			j+=fib(n-2); 
			thread_cnt++;
			}
    		}
    	}// end of parallel region
    	return i+j;
        
    }// end of else
}


int main (int argc, char *argv[]) {
    int result;
    printf("Doing sequential fibonacci:\n");
    result = fib(5);
    printf("Result is %d\n", result);
    printf("threads launched %d\n", thread_cnt);
    return 0;
}
