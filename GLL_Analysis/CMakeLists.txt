cmake_minimum_required(VERSION 3.5)
project(GLL_Analysis)

set(GLL_SRC GLL_Analysis.h GLL_Analysis.cpp GSS_node.h GSS_node.cpp)

include_directories(${GrammarAnalysis_SOURCE_DIR}/include)

add_executable(GLL_AnalysisRunner ${GLL_SRC} GLL_AnalysisRunner.cpp)
add_executable(GLL_AnalysisTest ${GLL_SRC} GLL_AnalysisTest.cpp)

target_link_libraries(GLL_AnalysisRunner grammarAndAutomationReader)
target_link_libraries(GLL_AnalysisTest grammarAndAutomationReader)