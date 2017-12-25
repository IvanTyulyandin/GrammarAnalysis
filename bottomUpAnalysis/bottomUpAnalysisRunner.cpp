//
// Created by ivan on 25/12/17
//

#include <iostream>
#include "grammarAndAutomationReader.h"

using specialStatesVector = std::vector<int>;
using mapToSpecialStatesType = std::map<std::string, specialStatesVector>;


int main(int argc, char* argv[])
{
    automationType automation;
    mapToSpecialStatesType startStates;
    mapToSpecialStatesType finalStates;
    unsigned long numOfStates;

    recursiveFiniteAutomationReader("Q1RFA.txt", automation, numOfStates, startStates, finalStates);

    for (auto &vec : startStates)
    {
        std::cout << vec.first + ": ";
        for (auto &j : vec.second)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    for (auto &vec : finalStates)
    {
        std::cout << vec.first + ": ";
        for (auto &j : vec.second)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    std::cout << numOfStates << std::endl;
}

