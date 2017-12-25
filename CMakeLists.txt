cmake_minimum_required(VERSION 3.5)
project(GrammarAnalysis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES grammarAndAutomationReader.cpp)
set(HEADERS grammarAndAutomationReader.h)

set(MATRIX_SRC matrixAnalysis.h matrixAnalysis.cpp)
set(BOTTOM_UP_SRC bottomUpAnalysisRunner.cpp)
add_executable(matrixAnalysisRunner ${HEADERS} ${SOURCES} ${MATRIX_SRC} matrixAnalysisRunner.cpp)
add_executable(matrixAnalysisTest ${HEADERS} ${SOURCES} ${MATRIX_SRC} matrixAnalysisTest.cpp)
add_executable(bottomUpAnalysisRunner ${HEADERS} ${SOURCES} ${BOTTOM_UP_SRC})

