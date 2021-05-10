#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <mpi.h>

#define N 5 // 5 for geekforgeek 100 if i got the java program to work.

int extract_min(int* Q, bool isInvalid[]){
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

int main(int argc, char **argv){
    // from geekforgeek
    int graph[N][N] =   { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };;

    int Q[N];
    //int* ptrQ = &Q[0];
    
    bool isInvalid [N];
    //bool* ptrIsInvalid = &isInvalid[0];
    
    int parents[N];
    //int* ptrparents = &parents[0];

    int num_procs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        for(int i = 0; i < N; i++){
            isInvalid[i] = false;
            Q[i] = INT_MAX;
            parents[i] = -1;
        
        }

        Q[0] = 0; 
    }
    
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
    
    if(rank == 0){
        printMST(parents, graph);
    }
    
    MPI_Finalize();
    return 0;
}