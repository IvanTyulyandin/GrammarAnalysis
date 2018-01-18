//
// Created by ivan on 25/12/17
//

#include <iostream>
#include <chrono>
#include "grammarAndAutomationReader.h"
#include "bottomUpAnalysis.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Need two args - file with grammar(RFA) and file with automation" << std::endl;
        exit(1);
    }
    auto start_time = std::chrono::steady_clock::now();
    auto bottomUpAnalysisWorker = new bottomUpAnalysis(argv[1], argv[2]);
    bottomUpAnalysisWorker->runAnalysis();
    if (argc > 3)
    {
        bottomUpAnalysisWorker->printResult(argv[3]);
    }
    else
    {
        bottomUpAnalysisWorker->printResult();
    }
    std::cout << "Count result = " << bottomUpAnalysisWorker->countResult() << std::endl;
    delete(bottomUpAnalysisWorker);

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time: " << duration.count() << " sec\n";
}

