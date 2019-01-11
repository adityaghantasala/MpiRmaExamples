cmake_minimum_required (VERSION 2.6)
project (RmaArrayOpp)
file(GLOB SOURCES src/*.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

# MPI Package is required. So finding it
find_package(MPI REQUIRED)
# Including the MPI files for compiling
include_directories(${MPI_INCLUDE_PATH} "src/")

add_executable(RmaArrayOpp main.cpp)

if(MPI_COMPILE_FLAGS)
    set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
endif()

if(MPI_LINK_FLAGS)
    set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
endif()

target_link_libraries(RmaArrayOpp ${MPI_LIBRARIES})