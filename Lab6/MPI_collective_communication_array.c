#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int num_proc, my_rank;
    int arraySize = 100;
    int isend[arraySize];    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    int equalChunks = arraySize/num_proc;
    if(my_rank == 0){
        for(int i = 0; i < arraySize;i++){
            isend[i] = i;
        }
    }
    
    int procArray[equalChunks];
    MPI_Scatter(&isend,equalChunks,MPI_INT,procArray,equalChunks,MPI_INT,0,MPI_COMM_WORLD);

    for(int i = 0; i < equalChunks;i++){
        procArray[i] += my_rank;
    }

    MPI_Gather(&procArray,equalChunks,MPI_INT,isend,equalChunks,MPI_INT,0,MPI_COMM_WORLD);

    if(my_rank == 0){
        for(int i = 0; i < arraySize;i++){
            printf("%d\n",isend[i]);
        }
    }

    MPI_Finalize();


    return 0;
}