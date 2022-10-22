#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main() {
    MPI_Init(NULL, NULL);

    int procid;
    int nprocs;

    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nprocs);
    MPI_Comm_rank(comm, &procid);

    int send = nprocs - procid;
    int recv = send;
    int peer;
    
    if(procid == 0) {
        peer = 1;
    }
    if(procid == 1 ) {
        peer = 0;
    }
    
    for(int i=0; i < nprocs; i++) {
        if(i % 2 == 0) {
            if(procid % 2 == 0) {
                peer = procid + 1;
            } else if (procid % 2 == 1) {
                peer = procid - 1;
            }

            if(peer > nprocs - 1 || peer < 0) {
                peer = MPI_PROC_NULL;
            }
            
            MPI_Sendrecv(&send, 1, MPI_INT,peer,0,
                            &recv, 1, MPI_INT, peer, 0 , 
                            comm, MPI_STATUS_IGNORE);

            if(procid % 2 == 0) {
                if(send > recv) {
                    send = recv;
                }
            }
            if(procid % 2 == 1) {
                if(send < recv) {
                    send = recv;
                }
            }
        }

        if(i % 2 == 1) {
            if(procid % 2 == 1) {
                peer = procid + 1;
            } else if (procid % 2 == 0) {
                peer = procid - 1;
            }

            if(peer > nprocs - 1 || peer < 0) {
                peer = MPI_PROC_NULL;
            }
            
            MPI_Sendrecv(&send, 1, MPI_INT,peer,0,
                            &recv, 1, MPI_INT, peer, 0 , 
                            comm, MPI_STATUS_IGNORE);
            if(procid % 2 == 1) {
                if(send > recv) {
                    send = recv;
                }
            }
            if(procid % 2 == 0) {
                if(send < recv) {
                    send = recv;
                }
            }
        }
    }
    for(int i=0; i < nprocs; i++) {
        if(procid == i) {
            printf("%d - process %d\n", send, procid);
            break;
        }
    }

    MPI_Finalize();

    return 0;
}