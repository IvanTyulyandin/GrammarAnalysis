cmake_minimum_required(VERSION 3.5)
project(matrixAnalysis)

set(MATRIX_SRC matrixAnalysis.h matrixAnalysis.cpp)

include_directories(${GrammarAnalysis_SOURCE_DIR}/include)

add_executable(matrixAnalysisTest ${MATRIX_SRC} matrixAnalysisTest.cpp)
add_executable(matrixAnalysisRunner ${MATRIX_SRC} matrixAnalysisRunner.cpp)

target_link_libraries(matrixAnalysisTest grammarAndAutomationReader)
target_link_libraries(matrixAnalysisRunner grammarAndAutomationReader)