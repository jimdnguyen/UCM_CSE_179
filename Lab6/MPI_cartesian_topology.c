#include<mpi.h>
#include<stdio.h>

 // https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/mpi-process-topologies

 // 0   1
 // 2   3
 

int main(int argc, char *argv[])
{
    int rank, size;
    int n = 2;
    MPI_Comm comm;
    int dim[n], period[n], reorder;
    int coord[n], id;
    int tmpCoord[n], tmp2Coord[n];
    int up,down,left,right;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dim[0]=2; dim[1]=2;
    period[0]=1; period[1]=1;
    reorder=0;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);
    
    MPI_Cart_coords(comm, rank, 2 ,coord);      
    MPI_Cart_rank(comm,coord,&id);
    if(rank == id){
        printf("MPI process %d @ (%d , %d) has the same rank as the local rank. \n",rank, coord[0],coord[1]);
    } else{
        printf("MPI process %d @ (%d , %d) does not have the same rank as the local rank. \n",rank, coord[0],coord[1]);
    }
    

    MPI_Cart_shift(comm,0,1,&up,&down);
    MPI_Cart_shift(comm,1,1,&left,&right);
    if(rank % 2 == 0){
        tmpCoord[0] = coord[0];
        tmpCoord[1] = coord[1];
        MPI_Cart_coords(comm, up, 2 ,coord);
        tmp2Coord[0] = coord[0];
        tmp2Coord[1] = coord[1];
        MPI_Cart_coords(comm, right, 2 ,coord);
        printf("The neighbor (%d , %d) is at ID: %d.", coord[0],coord[1], up);
        printf(" The neighbor (%d , %d) is at ID: %d.\n",coord[0],coord[1], right);
        printf("Avg rank between (%d , %d) and (%d, %d) is: %d. ", tmpCoord[0], tmpCoord[1], coord[0], coord[1], (up + rank)/2);        
        printf("Avg rank between (%d , %d) and (%d, %d) is: %d\n\n",tmpCoord[0], tmpCoord[1], coord[0], coord[1], (right + rank)/2);
    }
    else {
        tmpCoord[0] = coord[0];
        tmpCoord[1] = coord[1];
        MPI_Cart_coords(comm, up, 2 ,coord);
        tmp2Coord[0] = coord[0];
        tmp2Coord[1] = coord[1];
        MPI_Cart_coords(comm, right, 2 ,coord);
        printf("The neighbor (%d , %d) is at ID: %d.", coord[0],coord[1], up);
        printf(" The neighbor (%d , %d) is at ID: %d.\n",coord[0],coord[1], left);
        printf("Avg rank between (%d , %d) and (%d, %d) is: %d. ", tmpCoord[0], tmpCoord[1], coord[0], coord[1], (up + rank)/2);        
        printf("Avg rank between (%d , %d) and (%d, %d) is: %d\n\n",tmpCoord[0], tmpCoord[1], coord[0], coord[1], (left + rank)/2);
    }

    MPI_Finalize();
    return 0;
}