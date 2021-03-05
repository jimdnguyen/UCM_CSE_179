#include <stdio.h>
#include <mpi.h>

/*
Using the above MPI_simple.c as a model, write a program that sends a message around a ring of
processes. 
More precisely, processes i>0 should wait to receive a message from the process with rank i-1, 
verify that the message contains the integer i-1, 
replace the integer i-1 with the integer i, and then 
send the modified message to the process with rank i+1. 

For example, 
the process with rank 0 should send a message containing its rank to the process with rank 1, 
receive a message from the process with rank n-1, and then 
print the message to the screen.

Test the program with different arguments for –np witch, so that you are confident it works correctly.
Measure the execution time with different number of MPI processes.

*/

int main(int argc, char *argv[]) {

    int numprocs, rank, namelen, nextproc, prevproc, i;
    double startTime,endTime,totalTime;
    startTime = MPI_Wtime();
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    nextproc = (rank + 1) % numprocs;
    prevproc = (rank + numprocs - 1)% numprocs;
    i = 0;

    
    if(rank == 0){
        MPI_Send(&i, 1, MPI_INT,nextproc,0,MPI_COMM_WORLD);
        i++;
    } else if(rank > 0){
        MPI_Recv(&i, numprocs, MPI_INT, prevproc,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);        
        printf("Process %d received i value %d from Process %d\n", rank, i, prevproc);
        i++;
        MPI_Send(&i, 1, MPI_INT,nextproc,0,MPI_COMM_WORLD);
    }

    if(rank == 0){
        MPI_Recv(&i, numprocs, MPI_INT, prevproc,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Process %d received i value %d from Process %d\n", rank, i, prevproc);
    }

    endTime = MPI_Wtime();
    totalTime = endTime - startTime;
    printf("The ring took us %f seconds\n",totalTime);
    MPI_Finalize();
    
    
    

    return 0;
}
