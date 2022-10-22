#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int fib(int n) {
    if (n<2)
        return n;
    else {
        int i, j;
       
        #pragma omp task shared(i) firstprivate(n) 
        i=fib(n-1);
       
        #pragma omp task shared(j) firstprivate(n) 
        j=fib(n-2);
       
        #pragma omp taskwait
        return i+j;
    }
}


int main (int argc, char *argv[]) {
    int result;
    printf("Doing sequential fibonacci:\n");
   
    #pragma omp parallel
    {
        #pragma omp single
        result = fib(4);
    }
   
    printf("Result is %d\n", result);
    return 0;
}
