#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){

    int i,rank,size,offset, bufsize, nints, N=40;
    MPI_File fhr;
    MPI_Offset filesize;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);    
    int buf[N]; 
    nints = bufsize/sizeof(int);
    int bufw[N];
    for(i = 0; i < N;i++){
        bufw[i] = i;
    }

    offset = 10 * rank;

    MPI_File_open(MPI_COMM_WORLD,"datafile2",MPI_MODE_RDONLY,MPI_INFO_NULL, &fhr);

    MPI_File_get_size(fhr, &filesize);

    bufsize = filesize/size;


    //MPI_File_read_at(fhr,0,buf,offset + 10,MPI_INT, &status);

    MPI_File_read_at(fhr,rank*bufsize,buf,nints,MPI_INT, &status);

    //printf("\n Rank: %d, Offset: %d\n", rank, offset);

    printf("\n rank: %d, buf[%d]: %d\n",rank,rank*bufsize,buf[0]);

    

     

    MPI_File_close(&fhr);


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