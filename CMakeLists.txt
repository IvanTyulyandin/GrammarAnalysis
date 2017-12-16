cmake_minimum_required(VERSION 3.5)
project(GrammarAnalysis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES matrixAnalysis.cpp grammarAndAutomationReader.cpp)
set(HEADERS matrixAnalysis.h grammarAndAutomtionReader.h)
add_executable(matrixAnalysisRunner ${HEADERS} ${SOURCES} matrixAnalysisRunner.cpp)
add_executable(matrixAnalysisTest ${HEADERS} ${SOURCES} matrixAnalysisTest.cpp)

