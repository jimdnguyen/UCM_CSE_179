#include <stdio.h>
#include <mpi.h>
//#define FILESIZE 80

int main(int argc, char **argv){

    int i,rank,size,offset,nints, N=40;
    MPI_File fhrw;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //bufsize = FILESIZE/size;
    //nints = bufsize/sizeof(int);
    //int bufr[nints]; 
    int bufw[N];
    for(i = 0; i < N;i++){
        bufw[i] = i;
    }

    offset = 10 * rank;

    MPI_File_open(MPI_COMM_WORLD,"datafile",MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fhrw);

    printf("\n Rank: %d, Offset: %d\n", rank, offset);

    MPI_File_write_at(fhrw,0,bufw,offset + 10,MPI_INT, &status);    

    MPI_File_close(&fhrw);

    //MPI_File_open(MPI_COMM_WORLD,"datafile",MPI_MODE_RDONLY,MPI_INFO_NULL, &fhrw);

    //MPI_File_read_at(fhrw,rank*bufsize,bufr,nints,MPI_INT, &status);

    MPI_Finalize();

    return 0;
    
}

/*
READING A FILE
int rank, size, bufsize,nints;
    MPI_File fh;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    bufsize = FILESIZE/size;
    nints = bufsize/sizeof(int);
    int buf[nints];
    MPI_File_open(MPI_COMM_WORLD,"dfile",MPI_MODE_RDONLY,MPI_INFO_NULL,&fh);
    //MPI_File_seek(fh,rank * bufsize, MPI_SEEK_SET);
    //MPI_File_read(fh,buf,nints,MPI_INT, &status);
    MPI_File_read_at(fh,rank*bufsize,buf,nints,MPI_INT, &status);
    printf("\n rank: %d, buf[%d]: %d",rank,rank*bufsize,buf[0]);
    MPI_File_close(&fh);
    MPI_Finalize();
    return 0;


*/

/*
WRITING A FILE, recopy under offset =

MPI_File_open(MPI_COMM_WORLD,"datafile",MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fhw);

    printf("\n Rank: %d, Offset: %d\n", rank, offset);

    MPI_File_write_at(fhw,offset,buf,(N/size),MPI_INT, &status);

    MPI_File_close(&fhw);

    MPI_Finalize();
    return 0;

    //////////

    MPI_File_open(MPI_COMM_WORLD,"datafile3",MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fhw);

    printf("\n Rank: %d, Offset: %d\n", rank, offset);

    MPI_File_set_view(fhw,offset,MPI_INT,MPI_INT,"native",MPI_INFO_NULL);

    MPI_File_write(fhw,buf,(N/size),MPI_INT,&status);

    MPI_File_close(&fhw);

    MPI_Finalize();
*/