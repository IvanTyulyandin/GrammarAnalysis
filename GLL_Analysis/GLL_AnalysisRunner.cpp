//
// Created by ivan on 30/12/17.
//

#include <iostream>
#include <chrono>
#include "GLL_Analysis.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Need two args - file with grammar(RFA) and file with automation" << std::endl;
        exit(1);
    }
    auto start_time = std::chrono::steady_clock::now();
    auto GLLAnalysisWorker = new GLL_Analysis(argv[1], argv[2]);
    GLLAnalysisWorker->runAnalysis();
    if (argc > 3)
    {
        GLLAnalysisWorker->printResult(argv[3]);
    }
    else
    {
        GLLAnalysisWorker->printResult();
    }
    std::cout << "Count result = " << GLLAnalysisWorker->countResult() << std::endl;
    delete(GLLAnalysisWorker);

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time: " << duration.count() << " sec\n";
}