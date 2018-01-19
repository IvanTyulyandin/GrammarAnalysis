#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Release .

make -j 4

cd matrixAnalysis
./matrixAnalysisTest

cd ../bottomUpAnalysis
./bottomUpAnalysisTest

cd ../GLL_Analysis
./GLL_AnalysisTest

echo "All tests successfully passed!"