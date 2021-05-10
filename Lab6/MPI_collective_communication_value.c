#include <stdio.h>
#include <mpi.h>

//https://stackoverflow.com/questions/13867809/how-are-mpi-scatter-and-mpi-gather-used-from-c

int main(int argc, char *argv[]) {

    int num_proc, my_rank;    
    int squVar;
    double startTime,endTime,totalTime;
    startTime = MPI_Wtime();
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int isend[num_proc], irecv;

    if(my_rank == 0){
        for(int i = 0; i < num_proc;i++){
            isend[i] = i + 1;
        }
    }

    MPI_Scatter(isend,1,MPI_INT,&squVar,1,MPI_INT,0,MPI_COMM_WORLD);

    printf("rank = %d has this data: %d\n",my_rank,squVar);    

    squVar *= squVar;

    printf("rank = %d squared the data to: %d\n", my_rank, squVar);

    endTime = MPI_Wtime();
    totalTime = endTime - startTime;
    printf("Squaring took us %f seconds\n",totalTime);

    MPI_Finalize();


    return 0;
}