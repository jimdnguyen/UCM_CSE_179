#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

const int n = 512;
#define THREADS 4

void standardMultiplication(int A[][n], int x[][n], int b[][n], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            b[i][j] = 0;
            for(int k = 0; k < n; k++){
                b[i][j] += A[i][k] * x[k][j];
            }
        }
    }
}

void parallelMultiplication(int A[][n], int x[][n], int b[][n], int n){
    int tid;
    //#pragma omp parallel private(tid)
    #pragma omp parallel private(tid) num_threads(THREADS)
    //#pragma omp parallel private(tid) schedule(dynamic) num_threads(THREADS)
    {
        tid = omp_get_thread_num();
        //#pragma omp for  //default schedule static
        #pragma omp for schedule(static) 
        //#pragma omp for schedule(dynamic)
        
        
        for(int i = 0; i < n; i++){
            
            for(int j = 0; j < n; j++){
                b[i][j] = 0;
                for(int k = 0; k < n; k++){
                    b[i][j] += A[i][k] * x[k][j];
                }
            }
        }
        if(tid == 0){
            int nthreads = omp_get_num_threads();
            std::cout<<"Total number of threads is: "<<nthreads<<" threads!\n";
        }
    }     
}

int main() {   
int nthreads,tid;
int A[n][n];
int x[n][n];

int b[n][n];

srand(time(0));

for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        A[i][j] = rand()/RAND_MAX;
        x[i][j] = rand()/RAND_MAX;
    }
}

struct timeval start, end;

gettimeofday(&start,NULL);
standardMultiplication(A,x,b,n);
gettimeofday(&end,NULL);
printf("Serial code takes %ld micro seconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

gettimeofday(&start,NULL);
parallelMultiplication(A,x,b,n);
gettimeofday(&end,NULL);
printf("OpenMP code takes %ld micro seconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

return 0;
}