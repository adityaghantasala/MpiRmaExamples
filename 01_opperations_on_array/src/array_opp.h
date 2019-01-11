//
//  License:		 GPL License. Look LICENSE.txt
//
//
//  Main authors:    Aditya Ghantasala
//

#if !defined( KRATOS_VTK_OUTPUT_H_INCLUDED )
#define KRATOS_VTK_OUTPUT_H_INCLUDED

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "mpi.h"


class RmaMPIOppTest {

public:

    RmaMPIOppTest(const std::string InputFile);

    ~RmaMPIOppTest();


private:

    std::vector<int> mVectorPart;
    std::vector<int> mVectorGlobal;
    std::string mInputFileName;
    MPI_Win mMpiWindow;

    void ReadInputFile();
    int GetKeyWordPosition(std::ifstream& File, std::string KeyWord) const;
    void InitialieMpi() const;
    void FinalizeMpi() const;

    void CreateWindow();

};




#endif