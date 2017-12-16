#include <iostream>
#include <fstream>
#include "matrixAnalysis.h"
#include "grammarAndAutomtionReader.h"

MatrixAnalysis::MatrixAnalysis(const std::string &grammarInput,
                               const std::string &automationInput)
{
    grammarReader(grammarInput, grammar);
    automationReader(automationInput, automation, numOfStates);

    matrix = matrixType(numOfStates, std::vector<std::vector<std::string>>(numOfStates,
                                                                          std::vector<std::string>(0)));
}

void MatrixAnalysis::printGrammar()
{
    for (const auto &mapElem : grammar)
    {
        std::cout << mapElem.first << "->";
        for (const auto &rule : mapElem.second)
        {
            for (const auto &partOfRule : rule)
            {
                std::cout << partOfRule << " | ";
            }
        }
        std::cout << std::endl;
    }
}

void MatrixAnalysis::printAutomation()
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

void MatrixAnalysis::printMatrix()
{
    for (auto &row : matrix)
    {
        for (auto &col : row)
        {
            for (auto &elem : col)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
        std::cout << "---" <<  std::endl;
    }
}

static nonTerminalsType findExistingRulesInGrammar(const grammarType &grammar,
                                                   const std::string &first,
                                                   const std::string &second)
{
    nonTerminalsType result = std::vector<std::string>(0);
    for (auto &rule : grammar)
    {
        for (auto &rightPart : rule.second) // rightPart - vector of strings
        {
            if (rightPart[0] == first && rightPart[1] == second) // we have ChNF
            {
                result.push_back(rule.first);
            }
        }
    }

    return result;
}

static void addNotExistingNonTerminals(nonTerminalsType &matrixElem,
                                                const nonTerminalsType &toAdd,
                                                bool &wasAdded)
{
    auto areExistInMatrixElem = [&matrixElem](std::string wanted) -> bool
    {
        for (auto &nonTerminal : matrixElem)
        {
            if (nonTerminal == wanted)
            {
                return true;
            }
        }
        return false;
    };

    for (auto &nonTerminal : toAdd)
    {
        if (!areExistInMatrixElem(nonTerminal))
        {
            matrixElem.push_back(nonTerminal);
            wasAdded = true;
        }
    }
}

int MatrixAnalysis::countResult()
{
    int res = 0;
    for (auto &row : matrix)
        for (auto &col : row)
            for (auto &elem : col)
            {
                if (elem == "S")
                {
                    res ++;
                }
            }
    return res;
}

void MatrixAnalysis::runAnalysis()
{
    // matrix init
    for (auto &i : automation)
    {
        // should push_back cos may be 2 or more ways
        const auto &terminal = std::get<2>(i);
        for (auto &rule : grammar)
            for (auto &right : rule.second)
                for (auto &partOfRule : right)
                {
                    if (terminal == partOfRule) // we have ChNF
                    {
                        matrix[std::get<0>(i)][std::get<1>(i)].push_back(rule.first);
                    }
                }
    }
    // matrix init end
    // main part of algorithm
    bool matrixChanged = true;
    while (matrixChanged)
    {
        matrixChanged = false;
        for (auto i = 0; i < numOfStates; i ++)
            for (auto j = 0; j < numOfStates; j ++)
                for (auto k = 0; k < numOfStates; k ++)
                    for (auto &ik : matrix[i][k]) // ik and kj - strings
                        for (auto &kj : matrix[k][j])
                        {
                            nonTerminalsType leftParts = findExistingRulesInGrammar(grammar, ik, kj);
                            // matrixChanged is passed by reference
                            addNotExistingNonTerminals(matrix[i][j], leftParts, matrixChanged);
                        }
    }
}

void MatrixAnalysis::printResult(const std::string &outputFileName)
{
    if (!outputFileName.empty())
    {
        std::ofstream outputFile(outputFileName, std::ofstream::out);
        for (int i = 0; i < numOfStates; i++)
            for (int j = 0; j < numOfStates; j++)
                for (auto &nonTerminal : matrix[i][j]) {
                    outputFile << i << "," << nonTerminal << "," << j << std::endl;
                }
    }
    else
    {
        for (int i = 0; i < numOfStates; i++)
            for (int j = 0; j < numOfStates; j++)
                for (auto &nonTerminal : matrix[i][j]) {
                    std::cout << i << "," << nonTerminal << "," << j << std::endl;
                }
    }
}