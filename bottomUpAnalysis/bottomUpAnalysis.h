//
// Created by ivan on 25/12/17.
//

#ifndef GRAMMARANALYSIS_BOTTOMUPANALYSIS_H
#define GRAMMARANALYSIS_BOTTOMUPANALYSIS_H

#include <string>
#include <map>
#include <vector>

using automationType = std::vector<std::tuple<int, int, const std::string>>;
using matrixType = std::vector<std::vector<bool>>;

using startStatesMap = std::map<int, std::vector<std::string>>;
using finalStatesMap = std::map<std::string, std::vector<int>>;

using indexArrayType = std::vector<std::pair<int, int>>;

class BottomUpAnalysis
{
public:

    BottomUpAnalysis(const std::string &RFAinput, const std::string &automationInput);

    void printAutomation() const;

    void printRFA() const;

    void printMatrix() const;

    void runAnalysis();

    int countResult();

    void printResult();

    void printResult(const std::string& fileName);

private:

    automationType automation;
    unsigned long numOfStatesInAutomation;

    automationType RFA;
    unsigned long numOfStatesInRFA;

    startStatesMap startStatesRFA;
    finalStatesMap finalStatesRFA;

    matrixType matrix;
    unsigned long matrixSize;

    indexArrayType indexArray;
};


#endif //GRAMMARANALYSIS_BOTTOMUPANALYSIS_H
