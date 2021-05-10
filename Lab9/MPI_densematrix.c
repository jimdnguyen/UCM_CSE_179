#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char **argv)
{

    int num_procs, rank, sumofCij;
    //int n;
    const int current_time = time(NULL);
    //printf("Enter n: ");
    //scanf("%d", &n);
    int n = 6; // this would be "user input n"
    //int q = 4; this is # of procs this would be "user input q"
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int A[n][n];
    int B[n][n];
    int C[n][n];
    srand(current_time + rank);
    if(rank == 0){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i][j] = (rand() % 5) + 1;
                B[i][j] = (rand() % 5) + 1;
            }
        }
    }

    MPI_Scatter(A,n*n/num_procs,MPI_INT,A,n*n/num_procs,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Bcast(B, n*n, MPI_INT,0,MPI_COMM_WORLD);

    if(rank > 0){
        for(int i = 0; i < num_procs; i++){
            for(int j = 0; j < num_procs; j++){
                //C[i][j] = 0;
                for(int k = 0; k < num_procs; k++){
                    //C[i][j] = C[i][j] + A[i][k] * B[k][j];
                    sumofCij = sumofCij + A[i][k] * B[k][j];
                }
                C[i][j] = sumofCij;
                sumofCij = 0;
            }
        }
    }

    MPI_Gather(C, n*n/num_procs,MPI_INT,C,n*n/num_procs,MPI_INT,0,MPI_COMM_WORLD);
    
    if(rank == 0){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                printf("%d ",C[i][j]);
            }
            printf("\n");
        }
    }
 
    MPI_Finalize();
    return 0;
}