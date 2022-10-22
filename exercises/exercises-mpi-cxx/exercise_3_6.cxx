#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main() {
    MPI_Init(NULL, NULL);
    
    float random_sum;
    float random_avg;
    MPI_Comm comm = MPI_COMM_WORLD;
    int procid;
    int nprocs;

    MPI_Comm_rank(comm, &procid);
    MPI_Comm_size(comm, &nprocs);\
    srand(procid);
    float random_num = 1 + rand() % 8;
    MPI_Reduce(&random_num, &random_sum, 1, MPI_FLOAT, MPI_SUM, 0, comm);
    printf("The process of %d out of %d produces %f \n", procid, nprocs, random_num);
    MPI_Finalize();

    if(procid == 0) {
        std::cout << "The sum is " << random_sum << std::endl;
        std::cout << "The average is " << random_sum/nprocs << std::endl;
    }
}