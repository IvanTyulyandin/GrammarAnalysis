cmake_minimum_required(VERSION 3.5)
project(GrammarAnalysis)

set(CMAKE_CXX_STANDARD 11)

add_executable(matrixAnalysisRunner matrixAnalysis.cpp grammarAndAutomationReader.cpp matrixAnalysisRunner.cpp matrixAnalysis.h grammarAndAutomtionReader.h)

