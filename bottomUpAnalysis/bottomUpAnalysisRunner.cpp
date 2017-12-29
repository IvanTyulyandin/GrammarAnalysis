//
// Created by ivan on 25/12/17
//

#include <iostream>
#include "grammarAndAutomationReader.h"
#include "bottomUpAnalysis.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Need two args - file with grammar and file with automation" << std::endl;
        exit(1);
    }
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
    delete(bottomUpAnalysisWorker);
}

