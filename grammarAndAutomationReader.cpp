//
// Created by ivan on 16/12/17.
//
#include <iostream>
#include <regex>
#include <fstream>

#include "grammarAndAutomtionReader.h"

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

    std::getline(fileStream, curString);
    while (!std::regex_search(curString, statesInString))
    {
        std::getline(fileStream, curString);
    }

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
