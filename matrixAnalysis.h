//
// Created by ivan on 16/12/17.
//
#ifndef GRAMMARANALYSIS_MATRIXANALYSIS_H
#define GRAMMARANALYSIS_MATRIXANALYSIS_H

#include <string>
#include <ostream>
#include <vector>
#include <map>

using rightPartType = std::vector<std::string>;
using grammarType = std::map<std::string, std::vector<rightPartType>>;
using automationType = std::vector<std::tuple<int, int, const std::string>>;
using nonTerminalsType = rightPartType;
using matrixType = std::vector<std::vector<nonTerminalsType>>;

class MatrixAnalysis
{
public:
    MatrixAnalysis(const std::string &grammarInput,
                   const std::string &automationInput);

    void printGrammar();

    void printAutomation();

    void printMatrix();

    int countResult();

    void runAnalysis();

    void printResult(const std::string &outputFileName);
private:

    grammarType grammar;
    automationType automation;
    unsigned long numOfStates;
    matrixType matrix;
};

#endif //GRAMMARANALYSIS_MATRIXANALYSIS_H
