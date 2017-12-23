//
// Created by ivan on 16/12/17.
//

#include <iostream>
#include "matrixAnalysis.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Need two args - file with grammar and file with automation" << std::endl;
        exit(1);
    }
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

