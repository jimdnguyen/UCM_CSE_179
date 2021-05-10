#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){

    int i,rank,size,offset, N=10;
    MPI_File fhw;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int bufw[N];
    int bufrw[N];
    int *buf00;
    int *buf01;
    int *buf02;
    int *buf03;
    int *buf04;
    for(i = 0; i < N;i++){
        bufw[i] = rank * 10 + i;
    }

    offset = 10 * rank;

    MPI_File_open(MPI_COMM_WORLD,"datafile2",MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fhw);

    MPI_File_set_view(fhw,offset*sizeof(int),MPI_INT,MPI_INT,"native",MPI_INFO_NULL);

    MPI_File_write_at(fhw,0,bufw,N,MPI_INT, &status);    

    MPI_File_close(&fhw);

    MPI_File_open(MPI_COMM_WORLD,"datafile2",MPI_MODE_RDONLY,MPI_INFO_NULL, &fhw);

    MPI_File_set_view(fhw,offset*sizeof(int),MPI_INT,MPI_INT,"native",MPI_INFO_NULL);

    //MPI_File_seek(fhw,offset*sizeof(int),MPI_SEEK_SET);

    MPI_File_read_at(fhw,0,bufw,N,MPI_INT,&status);
/*
    printf("Process %d has the following data: ",rank);

    for(int i = 0; i < N; i++){
        printf(" %d ",bufw[i]);
    }
    printf("\n");
*/
    MPI_File_close(&fhw);

    MPI_File_open(MPI_COMM_WORLD,"datafile3",MPI_MODE_CREATE|MPI_MODE_RDWR,MPI_INFO_NULL, &fhw);

    i = 0;
    while(i < 2){
        if(i == 0 || i == 1){
            bufrw[i] = bufw[i];
        }
        i++;
    }

    while( i < 4){
        if(i == 2 || i == 3){
            buf01[i] == bufw[i];
        }
        i++;
    }


    MPI_File_set_view(fhw,rank* 2*sizeof(int),MPI_INT,MPI_INT,"native",MPI_INFO_NULL);

    MPI_File_write_at(fhw,0,bufrw,N/5,MPI_INT, &status);

    MPI_File_close(&fhw);

    MPI_Finalize();

    return 0;
    
}

