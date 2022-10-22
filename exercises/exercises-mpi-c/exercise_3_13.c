#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
/*Let each process compute a random number. You want to print 
the maximum value and on what processor it is 
computed. What collective(s) do you use? Write a short program
*/
int main() {
    MPI_Init(NULL,NULL);
    MPI_Comm comm = MPI_COMM_WORLD;
    int procid;
    int nprocs;
    int root = 0;
    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &procid);

    srand(procid);
    int random_num = rand() % nprocs + 1;

    // Init memory of 100 ints
    int* send_buffer, *receive_buffer;
    if(procid == root) {
        receive_buffer = (int* )malloc(nprocs * sizeof(int));
        
    } else {
        receive_buffer = NULL;
    }
    MPI_Gather(&random_num,1,MPI_INT, 
                receive_buffer, 1, MPI_INT, root, comm);
    


    if(procid==root) {
        int maximum = receive_buffer[0];
        int i;
        int flag=0;
        for(i=0; i < nprocs; i++) {
            printf("%d ",receive_buffer[i]);
            if(receive_buffer[i] > maximum) {
                maximum = receive_buffer[i];
                flag = i;
            }
        }
        printf("\n");
        printf("The maximum number is %d, coming from process #%d\n", maximum,flag);
    }

    MPI_Finalize();
}