#include <iostream>
#include <vector>
#include <climits>
#include "omp.h"
#define N 5
#define THREADS 4
int extract_min(int* Q, bool* isInvalid){
    int min = INT_MAX;
    int u;
    for(int i = 0; i < N; i++){
        if(isInvalid[i] == false && Q[i] < min){
            min = Q[i];
            u = i;
        }
    }
    return u;
}

// from geekforgeek
int printMST(int parent[], int graph[N][N])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < N; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

int main(){
    int tid;
    #pragma omp parallel private(tid) num_threads(THREADS)
    {    
        
        tid = omp_get_thread_num();
        int graph[N][N] =   { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };;
    int* Q = new int[N];
    bool* isInvalid = new bool[N];
    int* parents = new int[N]; //going to output
    for(int i = 0; i < N; i++){
        isInvalid[i] = false;
        Q[i] = INT_MAX;
        parents[i] = -1;
    }

    Q[0] = 0; 

    for(int i = 0; i < N - 1; i++){                  
        int u = extract_min(Q, isInvalid);
        isInvalid[u] = true;
         for(int j = 0; j < N; j++){
            if(graph[u][j] && isInvalid[j] == false && graph[u][j] < Q[j]){
                Q[j] = graph[u][j];
                parents[j] = u;
                
            }
        }
    }
    //print array parents starting from 1
if(tid == 0){
   printMST(parents, graph);
}
    }
    

    return 0;
}