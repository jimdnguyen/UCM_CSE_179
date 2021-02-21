#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int N = 4096;
const int threads = 4;

int main(){
    omp_set_num_threads(threads);
    double runtime,runtime2,runtime3,runtime4,runtime5;
    int x[N];
    int y[N];
    int t[threads + 1];
    t[0] = 0;
    int tmpSum = 0;
    srand(time(0));

    for(int i = 0; i < N; i++){ //pushing random integers into x
       x[i] = rand();
       //x[i] = i + 1;
    }

     runtime = omp_get_wtime();
    /*
    y[0] = x[0];
    
    for(int j = 1; j < N; j++){
        y[j] = y[j-1] + x[j];
    }
    */   

     //code given to us by the TA

    #pragma omp parallel for schedule(static) firstprivate(tmpSum)
    for(int i = 0; i < N; i++){
        tmpSum += x[i];
        y[i] = tmpSum;
        t[omp_get_thread_num() + 1] = tmpSum;
    }
    runtime2 = omp_get_wtime() - runtime;

    for(int i = 1; i <threads;i++){
        t[i] += t[i-1];
    }
    runtime3 = omp_get_wtime() - runtime;

    #pragma omp parallel for schedule(static)
    for(int i = 0; i < N;i++){
        y[i] += t[omp_get_thread_num()];
    }
    runtime4 = omp_get_wtime() - runtime;

    

    /*
    for(int i = 0; i < N; i++){
        std::cout<<y[i]<<std::endl;
    }
    */

    printf("Number after doing prefix sum: %d\n",y[N-1]);
    runtime5 = omp_get_wtime() - runtime;

    

    printf("Spliting the array among the threads and each thread computes own (partial) prefix sum took %lf seconds,\nCreating an array t to perform the simple prefix sum took in %lf seconds,\nAll the threads adding T[threadid] to elements took %lf seconds,\nTotal runtime/Displaying the prefix sum took %lf seconds \n",runtime2,runtime3,runtime4,runtime5);
    return 0;
}