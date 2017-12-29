//
// Created by ivan on 16/12/17.
//

#ifndef GRAMMARANALYSIS_GRAMMARANDAUTOMTIONREADER_H
#define GRAMMARANALYSIS_GRAMMARANDAUTOMTIONREADER_H

#include <vector>
#include <string>
#include <map>

using rightPartType = std::vector<std::string>;
using grammarType = std::map<std::string, std::vector<rightPartType>>;
using automationType = std::vector<std::tuple<int, int, const std::string>>;
using startStatesMap = std::map<int, std::vector<std::string>>;
using finalStatesMap = std::map<std::string, std::vector<int>>;


void grammarReader(const std::string &fileName, grammarType &grammar);
void automationReader(const std::string &fileName, automationType &automation, unsigned long &numOfStates);
void recursiveFiniteAutomationReader(const std::string &fileName,
                                     automationType &automation,
                                     unsigned long &numOfStates,
                                     startStatesMap &startStates,
                                     finalStatesMap &finalStates);
#endif //GRAMMARANALYSIS_GRAMMARANDAUTOMTIONREADER_H
