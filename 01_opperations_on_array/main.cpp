//
//  License:		 GPL License. Look LICENSE.txt
//
//
//  Main authors:    Aditya Ghantasala
//

#include <iostream>
#include <fstream>
#include "mpi.h"
#include "array_opp.h"

#define NUM_ELEMENT 4

int main(int argc, char **argv)
{

  RmaMPIOppTest opp("../input_files/array_proc");

  // Get the current rank and total ranks
  int proc_id, num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if (num_procs > 4 && proc_id == 0)
  {
    std::cout << "This example can only be run maximum with 4 processors !.\n Currently this is run with " << num_procs << std::endl;
    exit(-1);
  }

  std::cout << "Current process :: " << proc_id << std::endl;
  std::cout << "Total process :: " << num_procs << std::endl;

  opp.SynchronizeData();
  opp.ModSynchronizeData();

  return 0;
}
