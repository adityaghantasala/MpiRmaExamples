//
//  License:		 GPL License. Look LICENSE.txt
//
//
//  Main authors:    Aditya Ghantasala
//

#include "array_opp.h"
#include <sstream>

RmaMPIOppTest::RmaMPIOppTest(const std::string FileName):mInputFileName(FileName)
{
    InitialieMpi();
    MPI_Comm_rank(MPI_COMM_WORLD, &mCurrentRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mNumberOfProc);
    if(mNumberOfProc != 1)
        mInputFileName = mInputFileName+"_"+std::to_string(mCurrentRank+1)+".txt";
    else
        mInputFileName = mInputFileName+".txt";

    std::cout<<"InputFileName for proc :: "<<mCurrentRank<<" is : "<<mInputFileName<<std::endl;
    ReadInputFile();
    CreateWindow();
}

RmaMPIOppTest::~RmaMPIOppTest()
{
    MPI_Win_free(&mMpiWindow);
    FinalizeMpi();
}

void RmaMPIOppTest::CreateWindow()
{
    int size_local_vector = mVectorPart.size();
    int size_global = 0;
    MPI_Allreduce(&size_local_vector, &size_global, 1, MPI_INT,MPI_SUM,MPI_COMM_WORLD);

    mVectorGlobal.resize(size_global);
    MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &mMpiWindow);

    MPI_Win_attach(mMpiWindow, &mVectorPart[0], mVectorPart.size()*sizeof(int));

    //MPI_Win_allocate(mVectorPart.size()*sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &mVectorPart[0], &mMpiWindow);
}


void RmaMPIOppTest::SynchronizeData()
{
    if(mCurrentRank == 0){

        int i=0;
        for (const auto& val : mVectorPart)
        {
           mVectorGlobal[i] = val;
           ++i;
        }

        for(int rank=1; rank<mNumberOfProc; ++rank)
        {
            MPI_Get(&mVectorGlobal[rank*4], 4, MPI_INT, rank, 0, 4, MPI_INT, mMpiWindow);
        }

        for (const auto& val : mVectorGlobal)
            std::cout<<"mVectorGlobal :: "<<val<<std::endl;
    }
}


void RmaMPIOppTest::InitialieMpi() const
{
    int initialized;
    MPI_Initialized(&initialized);
    if (!initialized)
        MPI_Init(NULL, NULL);
}

void RmaMPIOppTest::FinalizeMpi() const
{
    int finalized;
    MPI_Finalized(&finalized);
    if (!finalized)
        MPI_Finalize();
}

void RmaMPIOppTest::ReadInputFile()
{
    std::ifstream this_proc_file (mInputFileName, std::ios::in);
    int count=0;
    double tmp_double;
    std::string tmp_string;
    std::string line;
    int num_entries;

    int position = GetKeyWordPosition(this_proc_file, "NUM_ENTRIES");

    this_proc_file.seekg (position);
    getline(this_proc_file, line);
    std::stringstream line_stream(line);
    line_stream >>tmp_string;
    line_stream >>num_entries;

    int temp_num;
    int num_entries_read = 0;
    while(getline(this_proc_file, line)) {
        ++num_entries_read;
        std::stringstream line_stream(line);
        line_stream >> temp_num;
        mVectorPart.push_back(temp_num);
        if(num_entries_read == num_entries)
            break;
    }
}

int RmaMPIOppTest::GetKeyWordPosition(std::ifstream& File, std::string KeyWord) const
{

    std::string line;
    int line_num=0;
    while(getline(File, line)) {
        ++line_num;
        std::stringstream line_stream(line);
        std::string line_part;
        if(line_stream >> line_part)
        {
            if(line_part == KeyWord)
            {
                break;
            }
        }
    }

    return line_num;
}
