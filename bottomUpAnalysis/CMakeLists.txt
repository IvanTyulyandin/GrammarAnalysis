cmake_minimum_required(VERSION 3.5)
project(bottomUpAnalysis)

set(BOTTOM_UP_SRC bottomUpAnalysis.h bottomUpAnalysis.cpp)

include_directories(${GrammarAnalysis_SOURCE_DIR}/include)

add_executable(bottomUpAnalysisRunner ${BOTTOM_UP_SRC} bottomUpAnalysisRunner.cpp)
add_executable(bottomUpAnalysisTest ${BOTTOM_UP_SRC} bottomUpAnalysisTest.cpp)

target_link_libraries(bottomUpAnalysisRunner grammarAndAutomationReader)
target_link_libraries(bottomUpAnalysisTest grammarAndAutomationReader)