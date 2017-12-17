//
// Created by ivan on 16/12/17.
//

#include <iostream>
#include "matrixAnalysis.h"

int main(int argc, char* argv[])
{
    auto matrixWorker = new MatrixAnalysis(argv[1], argv[2]);
    matrixWorker->runAnalysis();
    if (argc > 3)
    {
        matrixWorker->printResult(argv[3]);
    }
    else
    {
        matrixWorker->printResult();
    }
    delete(matrixWorker);
}

