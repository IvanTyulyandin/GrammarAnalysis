//
// Created by ivan on 16/12/17.
//

#include <iostream>
#include "matrixAnalysis.h"

int main(int argc, char* argv[])
{
    auto matrixWorker = new MatrixAnalysis(argv[1], argv[2]);
    matrixWorker->runAnalysis();
    std::cout << matrixWorker->countResult() << std::endl;
}

