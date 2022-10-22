#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main() {
    MPI_Init(NULL,NULL);
    int procid;
    int nprocs;

    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &procid);
    srand(time(NULL));
    int* send_buffer = (*int) malloc(nprocs*sizeof(int));
    int* receive_buffer = (*int) malloc(nprocs*sizeof(int));
    
    printf("Hello World!\n");


    MPI_Finalize();

}