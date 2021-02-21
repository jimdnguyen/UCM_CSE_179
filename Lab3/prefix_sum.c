#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

const int N = 4096;
const int threads = 4;

int main(){
    omp_set_num_threads(threads);
    double runtime;
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

    for(int i = 1; i <threads;i++){
        t[i] += t[i-1];
    }

    #pragma omp parallel for schedule(static)
    for(int i = 0; i < N;i++){
        y[i] += t[omp_get_thread_num()];
    }

    runtime = omp_get_wtime() - runtime;

    /*
    for(int i = 0; i < N; i++){
        std::cout<<y[i]<<std::endl;
    }
    */

    //std::cout<<std::endl<<y[N-1]<<std::endl<< N*(N+1)/2<<std::endl;

    

    printf(" This code ran in %lf seconds \n",runtime);
    return 0;
}