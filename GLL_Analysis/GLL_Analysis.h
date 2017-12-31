//
// Created by ivan on 30/12/17.
//

#ifndef GRAMMARANALYSIS_GLL_ANALYSIS_H
#define GRAMMARANALYSIS_GLL_ANALYSIS_H

#include <string>
#include <map>
#include <vector>
#include <queue>

#include "GSS_node.h"

using toEdgeType = std::vector<std::pair<int, std::string>>;
using stateEdgesType = std::map<int, toEdgeType>;

using automationType = std::vector<std::tuple<int, int, const std::string>>;

using startStatesMap = std::map<int, std::vector<std::string>>;
using finalStatesMap = std::map<std::string, std::vector<int>>;
using nonTermToStart = finalStatesMap;

using GSSType = std::vector<GSS_node>;

// config defined in GSS_node.h
using workListType = std::queue<config>;
using historyListType = std::vector<config>;

class GLL_Analysis {

public:

    GLL_Analysis(const std::string &RFAinput, const std::string &automationInput);

    void runAnalysis();

    int countResult() const;

    void printResult() const;

    void printResult(const std::string& fileName) const;

    void printHistory() const;

private:

    automationType automation;
    unsigned long numOfStatesInAutomation;

    automationType RFA;
    unsigned long numOfStatesInRFA;

    startStatesMap startStatesRFA;
    finalStatesMap finalStatesRFA;
    nonTermToStart nonTermStartPos;

    stateEdgesType automationEdges;
    stateEdgesType RFA_Edges;

    workListType workList;
    historyListType history;
    GSSType GSS;

    std::vector<std::string> nonTerms;

    int curId = 0;
};

#endif //GRAMMARANALYSIS_GLL_ANALYSIS_H
