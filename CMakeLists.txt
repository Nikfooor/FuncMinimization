cmake_minimum_required(VERSION 3.5.0)
project(FunctionMinimization VERSION 0.1.0 LANGUAGES C CXX)

add_executable(FunctionMinimization
    "Source/Main.cpp" 
    "Header/Function.h" 
    "Source/Function.cpp"
    "Source/Area.cpp" 
    "Header/Area.h"
    "Header/StopCriteria.h" 
    "Source/StopCriteria.cpp" 
    "Source/OptimizationMethod.cpp" 
    "Header/OptimizationMethod.h"
    "Header/TransferData.h"
    "Source/TransferData.cpp"
    "Source/vectorX.cpp"
    "Header/vectorX.h"
)

include_directories(Header)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET FunctionMinimization PROPERTY CXX_STANDARD 20)
endif()

include(CTest)
enable_testing()


