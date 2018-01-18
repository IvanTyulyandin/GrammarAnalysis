//
// Created by ivan on 16/12/17.
//

#include <iostream>
#include <chrono>
#include "matrixAnalysis.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Need two args - file with grammar and file with automation" << std::endl;
        exit(1);
    }
    auto start_time = std::chrono::steady_clock::now();
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
    std::cout << "Count result = " << matrixWorker->countResult() << std::endl;
    delete(matrixWorker);

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time: " << duration.count() << " sec\n";
}

