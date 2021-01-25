/****************************************************************
 ****
 **** This program file is part of the book 
 **** `Parallel programming with MPI and OpenMP'
 **** by Victor Eijkhout, eijkhout@tacc.utexas.edu
 ****
 **** copyright Victor Eijkhout 2012-2021
 ****
 **** MPI Exercise to illustrate pipelining
 ****
 ****************************************************************/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include <vector>
using namespace std;
#include <mpl/mpl.hpp>

#ifndef N
#define N 10
#endif

/*
 * Compare local data `mydata' against incoming `otherdata'
 * Set local data to negative if it occurs in the incoming
 */
void setdiff( vector<int> &mydata,const vector<int> &otherdata ) {
  auto n = mydata.size();
  for ( int i_my=0; i_my<n; i_my++) {
    int my = mydata[i_my];
    for ( int i_ot=0; i_ot<n; i_ot++ ) {
      int ot = otherdata[i_ot];
      if (my==ot) { mydata[i_my] = -1; break; }
    }
  }
}

/*
 * Print the filter array by first gathering it
 * Note: this is not a scalable thing to do.
 */
void print_distarray( const vector<int> filter,const mpl::communicator &comm,
		   string header, bool sort=false ) {
  int
    n = filter.size(),
    nprocs = comm.size(),
    procno = comm.rank();

  if (procno==0) {
    vector<int> global_filter( nprocs*filter.size() );
    comm.gather( 0,filter.data(),mpl::contiguous_layout<int>(n),
		 global_filter.data(),mpl::contiguous_layout<int>(n) );
    if (sort) std::sort( global_filter.begin(),global_filter.end() );
    stringstream filterout;
    filterout << header;
    for (int i=0; i<nprocs*n; i++)
      filterout << " " << setw(3) << global_filter[i];
    cout << filterout.str() << endl;
  } else {
    comm.gather( 0,filter.data(),mpl::contiguous_layout<int>(n) );
  }
}

int main(int argc,char **argv) {

  const mpl::communicator &comm_world = mpl::environment::comm_world();
  int nprocs,procno;
  // compute communicator rank and size
  nprocs = comm_world.size();
  procno = comm_world.rank();

  // set the default random number generator
  random_device r;
  default_random_engine generator{ r() };
  // distribution: int between 0 and nprocs
  uniform_int_distribution<int> distribution(0,2*N*nprocs);

  // Set `sendto' and `recvfrom'
  int sendto   = ( procno+1 ) % nprocs;
  int recvfrom = ( procno-1+nprocs ) % nprocs;

  /*
   * Generate random local and other data
   */
  vector<int> mydata(N), filter(N), result(N);
  for (int i=0; i<N; i++) {
    mydata[i] = distribution(generator);
    result[i] = mydata[i];
    filter[i] = distribution(generator);
  }

  print_distarray( mydata,comm_world,"Starting with" );
  print_distarray(filter,comm_world, "Filter:      ",true);

  /*
   * Exercise:
   * -- compute the global set difference 
   *    by passing the filter around the ring in a bucket brigade
   */
  for (int p=0; p<nprocs; p++) {
/**** your code here ****/
    setdiff( result,filter );
/**** your code here ****/
  }

  print_distarray( result,comm_world,"Ending with  " );

  /*
   * Correctness check:
   * `error' will be:
   * - the lowest process number where an error occured, or
   * - `nprocs' if no error.
   */
  double max_of_errors = 0;
  int
    error = max_of_errors > 1.e-12 ? procno : nprocs,
    errors=-1;
  comm_world.allreduce( mpl::min<int>(),error,errors );
  //MPI_Allreduce(&error,&errors,1,MPI_INT,MPI_MIN,comm);
  if (procno==0) {
    if (errors==nprocs) 
      printf("Finished; all results correct\n");
    else
      printf("First error occurred on proc %d\n",errors);
  }

  return 0;
}
