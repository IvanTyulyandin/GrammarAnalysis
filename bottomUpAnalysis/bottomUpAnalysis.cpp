//
// Created by ivan on 25/12/17.
//
#include <iostream>
#include <fstream>

#include "bottomUpAnalysis.h"
#include "grammarAndAutomationReader.h"

bottomUpAnalysis::bottomUpAnalysis(const std::string &RFAinput, const std::string &automationInput)
{
    recursiveFiniteAutomationReader(RFAinput, RFA, numOfStatesInRFA, startStatesRFA, finalStatesRFA);

    automationReader(automationInput, automation, numOfStatesInAutomation);

    matrixSize = numOfStatesInRFA * numOfStatesInAutomation;

    matrix = matrixType(matrixSize, std::vector<bool>(matrixSize, false));

    for (int i = 0; i < numOfStatesInAutomation; ++ i)
    {
        for (int j = 0; j < numOfStatesInRFA; ++ j)
        {
            indexArray.emplace_back(std::make_pair(i, j));
        }
    }
}

void bottomUpAnalysis::printAutomation() const
{
    for (auto &iter : automation)
    {
        std::cout << std::get<0>(iter)
                  << "->"
                  << std::get<1>(iter)
                  << " "
                  << std::get<2>(iter)
                  << std::endl;
    }
}

void bottomUpAnalysis::printRFA() const
{
    std::cout << "Start states for nonterminals:" << std::endl;
    for (auto &iter : startStatesRFA)
    {
        std::cout << iter.first + ": ";
        for (auto &states : iter.second)
        {
            std::cout << states + " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Final states for nonterminals:" << std::endl;
    for (auto &iter : finalStatesRFA)
    {
        std::cout << iter.first + ": ";
        for (auto &states : iter.second)
        {
            std::cout << states + " ";
        }
        std::cout << std::endl;
    }

    for (auto &iter : RFA)
    {
        std::cout << std::get<0>(iter)
                  << "->"
                  << std::get<1>(iter)
                  << " "
                  << std::get<2>(iter)
                  << std::endl;
    }
}

void bottomUpAnalysis::printMatrix() const
{
    for (int i = 0; i < matrixSize; ++ i)
    {
        for (int j = 0; j < matrixSize; ++ j)
        {
            if (matrix[i][j])
            {
                std::cout << "(" << indexArray[i].first << " " << indexArray[i].second << ") ";
                std::cout << "(" << indexArray[j].first << " " << indexArray[j].second << ')' << std::endl;
            }
        }
    }
}


void bottomUpAnalysis::runAnalysis()
{
    auto checkExistInDFA = [](const automationType &automation, int i, int j, const std::string &symbol) -> bool
    {
        for (auto &rule : automation)
        {
            if (std::get<0>(rule) == i && std::get<1>(rule) == j && std::get<2>(rule) == symbol)
            {
                return true;
            }
        }
        return false;
    };

    automationType newEdges = automation;

    bool needOneMoreStep;
    do
    {
        needOneMoreStep = false;

        // stage 1: add info about RFA and DFA to matrix

        bool matrixWasChanged;
        do
        {
            int startDFA = 0;
            int startGrm = 0;
            int finalDFA = 0;
            int finalGrm = 0;

            matrixWasChanged = false;

            for (auto &edge : newEdges)
            {
                startDFA = std::get<0>(edge);
                finalDFA = std::get<1>(edge);

                for (int i = 0; i < matrixSize; ++ i)
                    if (startDFA == indexArray[i].first)
                    {
                        startGrm = indexArray[i].second;
                        for (int j = 0; j < matrixSize; ++ j)
                            if (finalDFA == indexArray[j].first)
                            {
                                finalGrm = indexArray[j].second;
                                for (auto &grmRule : RFA)
                                    if (std::get<0>(grmRule) == startGrm && std::get<1>(grmRule) == finalGrm)
                                        if (std::get<2>(grmRule) == std::get<2>(edge))
                                            if ( ! matrix[i][j])
                                            {
                                                matrixWasChanged = true;
                                                matrix[i][j] = true;
                                            }
                            }
                    }
            }
        } while (matrixWasChanged);

        // stage 2: closure

        for (int k = 0; k < matrixSize; ++k)
        {
            std::vector<bool> &matrixK = matrix[k];
            for (int i = 0; i < matrixSize; ++ i)
            {
                std::vector<bool> &matrixI = matrix[i];
                if (matrixI[k])
                    for (int j = 0; j < matrixSize; ++ j)
                        if (matrixK[j])
                            matrixI[j] = true;
            }
        }

        // stage 3: add new edges to automation

        newEdges = std::vector<std::tuple<int, int, const std::string>>(0);
        for (int i = 0; i < matrixSize; ++i)
        {
            int startPos = indexArray[i].second;
            auto nonTerms = startStatesRFA.find(startPos);
            if (nonTerms != startStatesRFA.end())
                for (auto &nonTerminal : (*nonTerms).second)
                {
                    auto finalPositions = (*finalStatesRFA.find(nonTerminal)).second;
                    for (auto finalPos : finalPositions)
                        for (int j = 0; j < matrixSize; ++j)
                            if (matrix[i][j] && indexArray[j].second == finalPos)
                            {
                                int startDFA = indexArray[i].first;
                                int finalDFA = indexArray[j].first;
                                if (!checkExistInDFA(automation, startDFA, finalDFA, nonTerminal))
                                {
                                    automation.emplace_back(std::make_tuple(startDFA, finalDFA, nonTerminal));
                                    newEdges.emplace_back(std::make_tuple(startDFA, finalDFA, nonTerminal));
                                    needOneMoreStep = true;
                                }
                            }
                }
        }
    } while (needOneMoreStep);
}

int bottomUpAnalysis::countResult()
{
    int result = 0;
    for (auto & ruleDFA : automation)
    {
        if (std::get<2>(ruleDFA) == "S")
            ++ result;
    }
    return result;
}

void bottomUpAnalysis::printResult()
{
    for (auto & rule : automation)
    {
        const auto & symbol = std::get<2>(rule);
        if ((symbol.length() != 1 && symbol != "eps") || (! islower(symbol[0]) && ! isdigit(symbol[0])))
        {
            std::cout << std::get<0>(rule) << ',' << symbol << ',' << std::get<1>(rule) << std::endl;
        }
    }
}

void bottomUpAnalysis::printResult(const std::string& fileName)
{
    std::ofstream outputFile(fileName, std::ofstream::out);

    for (auto & rule : automation)
    {
        const auto & symbol = std::get<2>(rule);
        if ((symbol.length() != 1 && symbol != "eps") || (! islower(symbol[0]) && ! isdigit(symbol[0])))
        {
            outputFile << std::get<0>(rule) << ',' << symbol << ',' << std::get<1>(rule) << std::endl;
        }
    }

    outputFile.close();
}