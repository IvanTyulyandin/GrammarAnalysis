//
// Created by ivan on 25/12/17.
//

#ifndef GRAMMARANALYSIS_BOTTOMUPANALYSIS_H
#define GRAMMARANALYSIS_BOTTOMUPANALYSIS_H

#include <string>
#include <map>
#include <vector>

using automationType = std::vector<std::tuple<int, int, const std::string>>;
using specialStatesVector = std::vector<int>;
using mapToSpecialStatesType = std::map<std::string, specialStatesVector>;

class bottomUpAnalysis {

    bottomUpAnalysis(const std::string &RFAinput, const std::string &automationInput);

    void printAutomation() const;

    void printRFA() const;

    automationType automation;
    automationType RFA;
    specialStatesVector startStates;
    specialStatesVector final;
};


#endif //GRAMMARANALYSIS_BOTTOMUPANALYSIS_H
