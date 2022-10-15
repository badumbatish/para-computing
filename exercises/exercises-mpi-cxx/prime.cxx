/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming for Science and Engineering'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-9
 ****
 **** MPI Exercise 
 ****
 ****************************************************************/

#include <iostream>
#include <sstream>
using namespace std;
#include <mpi.h>
#include <mpl/mpl.hpp>

int main() {
  MPI_Comm comm = MPI_COMM_WORLD;
  int nprocs, procno;
  int bignum = 2000000111, maxfactor = 45200;
  stringstream proctext;
  
  MPI_Init(0,0);

  // Exercise:
  // -- Parallelize the do loop so that each processor
  //    tries different candidate numbers.
  // -- If a processors finds a factor, print it to the screen.

  // 1. Set loop bounds
/**** your code here ****/
MPI_Comm_rank(comm, &procno);
MPI_Comm_size(comm, &nprocs);
/* Divide the work by number of workers
gap = max_factor / nprocs;
start_gap = max_factor(procno-1/nprocs)
*/
int gap = maxfactor / nprocs;
int myfactor = (maxfactor/nprocs)*(procno);

if(myfactor == 0) myfactor = 2;
std::cout << "Process ID: " << procno << std::endl;
  // 2. Fill in loop header
  for (int i= myfactor; i <= myfactor+gap;i++
/**** your code here ****/
       ) {
    if (bignum%i==0) { 
      proctext << "Processor " << procno << " found factor " << i << endl;
      cerr << proctext.str(); proctext.clear();
    }
  }

  MPI_Finalize();
  return 0;
}
