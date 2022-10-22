#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main() {
    MPI_Init(NULL,NULL);
    MPI_Comm comm = MPI_COMM_WORLD;
    int nprocs;
    int procid;

    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &procid);

    int num;
    int successor = procid - 1;
    int predecessor = procid + 1;
    if(procid == 0) {
        num = 1;
        successor=procid;
    }
    if(procid == nprocs - 1) {
        predecessor = procid;
    }

    if(procid!=0)
        MPI_Recv(&num,1, MPI_INT,
            successor,0, comm, MPI_STATUS_IGNORE);

    if(procid != nprocs - 1)
        num+=1;
        MPI_Send(&num, 1, MPI_INT, 
            predecessor,0,comm);


    
    


    MPI_Finalize();
    if(procid == nprocs - 1) {
        printf("%d \n", num);
    }
 
    return 0;
}