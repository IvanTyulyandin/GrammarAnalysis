//
// Created by ivan on 16/12/17.
//
#include <iostream>
#include <regex>
#include <fstream>

#include "grammarAndAutomationReader.h"

static rightPartType split(std::string &s, char delim) {
    rightPartType result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
        {
            result.push_back(item);
        }
    }
    return result;
}

void automationReader(const std::string &fileName, automationType &automation, unsigned long &numOfStates)
{
    std::ifstream fileStream;
    fileStream.open(fileName, std::fstream::in);

    std::string curString;
    std::regex statesInString ("[0-9]+");

    do
    {
        std::getline(fileStream, curString);
    } while (!std::regex_search(curString, statesInString));

    // dirty hack - count ';' instead of reading names
    numOfStates = split(curString, ';').size();

    //regex for X -> Y[label="Z"]
    std::regex automationRule ("([0-9]+)"
                                       "( -> )"
                                       "([0-9]+)"
                                       "([^0-9]+\")"
                                       "([^\"]*)"
                                       "(\"])+");
    std::smatch res;

    std::regex closingBracket ("[}]+");

    while (std::getline(fileStream, curString))
    {
        if (!std::regex_search(curString, closingBracket))
        {
            if (std::regex_search(curString, res, automationRule))
            {
                automation.emplace_back(std::make_tuple<int, int, const std::string>(
                        std::stoi(res.str(1))
                        , std::stoi(res.str(3))
                        , res.str(5)));
            }
            else
            {
                std::cout << "Can't parse " << curString << " with regex ([0-9]+)( -> )([0-9]+)([^0-9]+\")[^\"]*)\"])+";
                exit(1);
            }
        }
        else
        {
            break;
        }
    }
    fileStream.close();
}


void grammarReader(const std::string &fileName, grammarType &grammar)
{

    std::ifstream fileStream;
    fileStream.open(fileName, std::fstream::in);

    std::string curString;
    std::string leftPart;
    std::string rightPart;

    std::regex grammarRule ("([A-z0-9]+)"
                                    "( : )"
                                    "([A-z0-9 ]+)");
    std::smatch res;

    while (std::getline(fileStream, curString))
    {
        if (std::regex_search(curString, res, grammarRule))
        {
            leftPart = res.str(1);
            rightPart = res.str(3);
        }
        else
        {
            std::cout << "Can't parse " << curString << " with regex ([A-z0-9]+)( : )([A-z0-9]+)";
            exit(1);
        }
        //adding to grammar
        auto iterForPlacement = grammar.find(leftPart);
        auto rightPartVector = split(rightPart, ' ');

        if (iterForPlacement == grammar.end())
        {
            // need add new rule
            auto vecRightParts = std::vector<rightPartType>();
            vecRightParts.push_back(rightPartVector);
            grammar.emplace(leftPart, vecRightParts);
        }
        else
        {
            // rule is existing, need to add rightPartVector
            (*iterForPlacement).second.push_back(rightPartVector);
        }
    }
    fileStream.close();
}

void recursiveFiniteAutomationReader(const std::string &fileName,
                                     automationType &automation,
                                     unsigned long &numOfStates,
                                     startStatesMap &startStates,
                                     finalStatesMap &finalStates)
{
    /*
     * structure of input RFA
     *
     * some info
     * line with state1; state2; ...
     * some notes about start and final states for nonterminals
     * rules for states
     *
     * why I don't reuse automation reader? bad architecture ¯\_(ツ)_/¯
     */

    std::ifstream fileStream;
    fileStream.open(fileName, std::fstream::in);

    std::string curString;
    std::regex statesInString ("[0-9]+");

    // parse string with states
    do
    {
        std::getline(fileStream, curString);
    } while (!std::regex_search(curString, statesInString));

    // dirty hack - count ';' instead of reading names
    numOfStates = split(curString, ';').size();

    // parse start and final notes
    std::regex stateDefinition ("([0-9]+)([[])");
    std::smatch res;

    while (!std::regex_search(curString, res, stateDefinition))
    {
        std::getline(fileStream, curString);
    }

    // now need to parse states, first one is in curString
    std::regex ruleRegex ("(->)");
    std::regex isStart ("(color=)");
    std::regex isFinal ("(shape=)");
    std::regex hasLabel ("(label=\")([^\"]+)");
    std::regex numberInStateDefRegex ("([0-9]+)");

    std::string label;
    int numOfStateInDef;

    while (!std::regex_search(curString, res, ruleRegex))
    {
        if (std::regex_search(curString, res, numberInStateDefRegex))
        {
            numOfStateInDef = std::stoi(res.str(1));
        }
        else
        {
            std::cout << "Incorrect format of state definition, expected X[label=\"Y\", ...], got "
                      << curString
                      << std::endl;
            exit(1);
        }

        if (std::regex_search(curString, res, hasLabel))
        {
            label = res.str(2);
            // this map state -> nonterminal
            if (std::regex_search(curString, res, isStart))
            {
                auto states = std::vector<std::string>(1, label);
                auto emplaceResult = startStates.emplace(numOfStateInDef, states);
                if (!std::get<1>(emplaceResult))
                {
                    auto iter = std::get<0>(emplaceResult);
                    (*iter).second.push_back(label);
                }
            }

            // this map nonterminal -> state
            if (std::regex_search(curString, res, isFinal))
            {
                auto states = std::vector<int>(1, numOfStateInDef);
                auto emplaceResult = finalStates.emplace(label, states);
                if (!std::get<1>(emplaceResult))
                {
                    auto iter = std::get<0>(emplaceResult);
                    (*iter).second.push_back(numOfStateInDef);
                }
            }
        }
        else
        {
            std::cout << "Expected label= in string " << curString << std::endl;
            exit(1);
        }

        std::getline(fileStream, curString);
    }

    //regex for X -> Y[label="Z"]
    std::regex automationRule ("([0-9]+)"
                                       "( -> )"
                                       "([0-9]+)"
                                       "([^0-9]+\")"
                                       "([^\"]*)"
                                       "(\"])+");

    std::regex closingBracket ("[}]+");

    do
    {
        if (!std::regex_search(curString, closingBracket))
        {
            if (std::regex_search(curString, res, automationRule))
            {
                automation.emplace_back(std::make_tuple<int, int, const std::string>(
                        std::stoi(res.str(1))
                        , std::stoi(res.str(3))
                        , res.str(5)));
            }
            else
            {
                std::cout << "Can't parse " << curString << " with regex ([0-9]+)( -> )([0-9]+)([^0-9]+\")[^\"]*)\"])+";
                exit(1);
            }
        }
        else
        {
            break;
        }
    } while (std::getline(fileStream, curString));
    fileStream.close();
}
