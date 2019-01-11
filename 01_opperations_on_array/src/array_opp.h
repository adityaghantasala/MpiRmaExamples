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

    std::vector<double> mVectorPart;
    std::string mInputFileName;

    void ReadInputFile();

};




#endif