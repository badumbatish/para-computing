/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%
   %%%% This program file is part of the book and course
   %%%% "Parallel Computing"
   %%%% by Victor Eijkhout, copyright 2013-2021
   %%%%
   %%%% proccount.c : counting procs and threads
   %%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include <stdlib.h>
#include <stdio.h>

#include "omp.h"

void nested_report() {
#pragma omp parallel
#pragma omp master
  printf("Parallel  : count %2d cores and %2d threads out of max %2d\n",
	 omp_get_num_procs(),omp_get_num_threads(),omp_get_max_threads());
}

int main(int argc,char **argv) {

  printf("---------------- Parallelism report ----------------\n");

  printf("Sequential: count %2d cores and %2d threads out of max %2d\n",
	 omp_get_num_procs(),omp_get_num_threads(),omp_get_max_threads());
#pragma omp parallel
#pragma omp master
  printf("Parallel  : count %2d cores and %2d threads out of max %2d\n",
	 omp_get_num_procs(),omp_get_num_threads(),omp_get_max_threads());

#pragma omp parallel
#pragma omp master
  nested_report();

  return 0;
}
