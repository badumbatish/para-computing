#include <iostream>
#include <mpi.h>

int main() {
    MPI_Init(NULL,NULL);
    int procid;
    int nprocs;

    int value[2] = {1,2};
    int value_sum[2];
    int sum;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &procid);
    MPI_Comm_size(comm, &nprocs);

    int target_proc = nprocs - 1;
    MPI_Reduce(value, &value_sum, 2, MPI_INT, MPI_SUM, target_proc, comm);
    MPI_Finalize();

    sum = value_sum[0] + value_sum[1];
    if(procid == target_proc) {
        std::cout << "Sum is : " << sum << std::endl;
    }
}