//
// Created by ivan on 30/12/17.
//
#include <iostream>
#include <chrono>
#include "GLL_Analysis.h"

int main() {
    constexpr int NUM_OF_TESTS = 11;
    std::string test_grammars[NUM_OF_TESTS] = {"../testRFA/Q1RFA.txt", "../testRFA/Q2RFA.txt"};

    constexpr int NUM_OF_GRAMMARS = 2;
    std::string testData[NUM_OF_TESTS] = {"../data/atom-primitive.dot",
                                          "../data/biomedical-measure-primitive.dot",
                                          "../data/foaf.dot",
                                          "../data/funding.dot",
                                          "../data/generations.dot",
                                          "../data/people-pets.dot",
                                          "../data/pizza.dot",
                                          "../data/skos.dot",
                                          "../data/travel.dot",
                                          "../data/univ-bench.dot",
                                          "../data/wine.dot"};

    int correctAnswers[NUM_OF_TESTS][NUM_OF_TESTS] =
            {
                    {15454, 15156, 4118, 17634, 2164, 9472, 56195, 810, 2499, 2540, 66572},
                    {122,   2871,  10,   1158,  0,    37,   1262,  1,   63,   81,   133}
            };


    auto start_time = std::chrono::steady_clock::now();
    int passedTestCount = 0;

    for (int i = 0; i < NUM_OF_GRAMMARS; i++) {
        for (int j = 0; j < NUM_OF_TESTS; j++) {
            GLL_Analysis gll_analysisWorker(test_grammars[i], testData[j]);
            std::cout << "Running test " + testData[j] + " on grammar " + test_grammars[i] + "..." << std::endl;
            gll_analysisWorker.runAnalysis();
            int res = gll_analysisWorker.countResult();
            if (res != correctAnswers[i][j]) {
                std::cout << "Test " + testData[j] + " on grammar " + test_grammars[i] + " failed! ";
                std::cout << "Expected " << correctAnswers[i][j] << ", got " << res << std::endl;
            } else {
                std::cout << "Test successfully passed" << std::endl;
                ++passedTestCount;
            }
        }
    }

    GLL_Analysis GLL_AnalysisWorker("../testRFA/myTestRFA1.txt", "../testDFA/myTestDFA1.txt");
    GLL_AnalysisWorker.runAnalysis();
    if (GLL_AnalysisWorker.countResult() == 16)
    {
        std::cout << "Additional test on grammar ../myTest1RFA.txt and DFA ../myTestDFA1.txt passed" << std::endl;
        ++ passedTestCount;
    }
    else
    {
        std::cout << "Additional test on grammar ../myTest1RFA.txt and DFA ../myTestDFA1.txt failed!";
    }
    
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time: " << duration.count() << " sec\n";
    std::cout << "Passed " << passedTestCount << '/' << NUM_OF_TESTS * NUM_OF_GRAMMARS + 1 << std::endl;
    return 0;
}