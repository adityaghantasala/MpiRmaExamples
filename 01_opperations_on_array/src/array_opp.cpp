//
//  License:		 GPL License. Look LICENSE.txt
//
//
//  Main authors:    Aditya Ghantasala
//

#include "array_opp.h"


RmaMPIOppTest::RmaMPIOppTest(const std::string FileName):mInputFileName(FileName)
{
    int proc_id, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    std::cout<<"From ArrayOpps :: this proc :: "<<proc_id<<std::endl;
    std::cout<<"From ArrayOpps :: total proc :: "<<num_procs<<std::endl;
}

RmaMPIOppTest::~RmaMPIOppTest()
{

}

void RmaMPIOppTest::ReadInputFile()
{

}
