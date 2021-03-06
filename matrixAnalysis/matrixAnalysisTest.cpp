//
// Created by ivan on 17/12/17.
//

#include <iostream>
#include <chrono>
#include "matrixAnalysis.h"

int main()
{
    constexpr int NUM_OF_TESTS = 11;
    std::string test_grammars[NUM_OF_TESTS] = {"../testGrammars/Q1.txt", "../testGrammars/Q2.txt"};

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
                    {122, 2871, 10, 1158, 0, 37, 1262, 1, 63, 81, 133}
            };


    auto start_time = std::chrono::steady_clock::now();
    int passedTestCount = 0;

    for (int i = 0; i < NUM_OF_GRAMMARS; i ++)
    {
        for (int j = 0; j < NUM_OF_TESTS; j ++)
        {
            MatrixAnalysis testMatrix(test_grammars[i], testData[j]);
            std::cout << "Running test: matrix analysis, DFA " + testData[j] + ", grammar " + test_grammars[i] + "..."
                      << std::endl;
            testMatrix.runAnalysis();
            int res = testMatrix.countResult();
            if (res != correctAnswers[i][j])
            {
                std::cout << "Test " + testData[j] + " on grammar " + test_grammars[i] + " failed! ";
                std::cout << "Expected " << correctAnswers[i][j] << ", got " << res << std::endl;
                exit(1);
            }
            else
            {
                std::cout << "Test successfully passed" << std::endl;
                ++ passedTestCount;
            }
        }
    }

    // additional tests

    auto additionalTests = std::vector<std::pair<std::string, std::string>>();
    additionalTests.emplace_back(std::make_pair("../testGrammars/1.txt", "../testDFA/DFA1.txt"));
    additionalTests.emplace_back(std::make_pair("../testGrammars/2.txt", "../testDFA/DFA2.txt"));
    additionalTests.emplace_back(std::make_pair("../testGrammars/3.txt", "../testDFA/DFA3.txt"));
    additionalTests.emplace_back(std::make_pair("../testGrammars/4.txt", "../testDFA/DFA4.txt"));
    additionalTests.emplace_back(std::make_pair("../testGrammars/5.txt", "../testDFA/DFA5.txt"));

    constexpr int correctAnswersAdditional[] = {16, 20, 1, 9, 6};

    int curTest = 0;
    for (auto &test : additionalTests)
    {
        std::cout << test.first << test.second << std::endl;

        MatrixAnalysis matrixAnalysisWorker(test.first, test.second);
        matrixAnalysisWorker.runAnalysis();
        if (matrixAnalysisWorker.countResult() == correctAnswersAdditional[curTest])
        {
            std::cout << "Additional test on grammar " << test.first << " " << test.second << " passed"
                      << std::endl;
            ++ passedTestCount;
        }
        else
        {
            std::cout
                    << "Additional test on grammar " << test.first << " " << test.second << " failed!"
                    << std::endl;
            exit(1);
        }

        ++ curTest;
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Time: " << duration.count() << " sec\n";
    std::cout << "Passed " << passedTestCount << '/'
              << NUM_OF_TESTS * NUM_OF_GRAMMARS + additionalTests.size() << std::endl;
    return 0;
}