//
// Created by ivan on 30/12/17.
//

#include <grammarAndAutomationReader.h>
#include <iostream>
#include <fstream>
#include "GLL_Analysis.h"

GLL_Analysis::GLL_Analysis(const std::string &RFAinput, const std::string &automationInput)
{
    recursiveFiniteAutomationReader(RFAinput, RFA, numOfStatesInRFA, startStatesRFA, finalStatesRFA);

    automationReader(automationInput, automation, numOfStatesInAutomation);

    int src;
    std::pair<int, std::string> info;

    for (auto &ruleDFA : automation)
    {
        info = std::make_pair(std::get<1>(ruleDFA), std::get<2>(ruleDFA));
        toEdgeType dstBy = std::vector<std::pair<int, std::string>>(1, info);

        src = std::get<0>(ruleDFA);
        auto insertPlace = automationEdges.emplace(src, dstBy);

        if ( ! insertPlace.second)
            (*insertPlace.first).second.push_back(info);
    }

    for (auto &ruleGrm : RFA)
    {
        auto symbol = std::get<2>(ruleGrm);
        info = std::make_pair(std::get<1>(ruleGrm), symbol);
        toEdgeType dstBy = std::vector<std::pair<int, std::string>>(1, info);

        src = std::get<0>(ruleGrm);
        auto insertPlace = RFA_Edges.emplace(src, dstBy);

        if ( ! insertPlace.second)
            (*insertPlace.first).second.push_back(info);

    }

    for (auto &iter : finalStatesRFA)
    {
        nonTerms.push_back(iter.first);
    }

    for (auto &iter : startStatesRFA)
    {
        for (auto &nonTerminal : iter.second)
        {
            auto emplaceRes = nonTermStartPos.emplace(nonTerminal, std::vector<int>(1, iter.first));
            if ( ! emplaceRes.second)
                (*emplaceRes.first).second.push_back(iter.first);
        }
    }

}

static void addToWorkList(const config& configuration, historyListType &history, workListType &workList)
{
    for (auto &iter : history)
        if (iter == configuration)
            return;

    workList.push(configuration);
    history.push_back(configuration);
}

static bool isNonterminal(const std::string &value)
{
    return ((value.length() != 1 && value != "eps") || (! islower(value[0]) && ! isdigit(value[0])));
}

// return id of gss_node
static int addToGSS(GSSType &GSS, GSS_node &value, int &curId)
{
    for (auto &iter : GSS)
    {
        if ((value.posInDFA == iter.posInDFA) && (value.nonTerm == iter.nonTerm))
        {
            return iter.SP;
        }
    }

    value.SP = curId;
    ++ curId;
    GSS.push_back(value);
    return value.SP;
}

static auto findBySP(GSSType &GSS, int SP) -> decltype(GSS.begin())
{
    for (auto iter = GSS.begin(); iter != GSS.end(); ++ iter)
    {
        if ((*iter).SP == SP)
        {
            return iter;
        }
    }
    return GSS.end();
}

void GLL_Analysis::printHistory() const
{
    for (auto &iter : history)
    {
        std::cout << iter.curPosInAutomation << " "
                  << iter.curPosInRFA << " "
                  << iter.SP << std::endl;
    }
}

void GLL_Analysis::runAnalysis()
{
    // stage 1: init GSS by (nonterminal, 0)
    for (int i = 0; i < numOfStatesInAutomation; ++ i)
    {
        for (auto &nonTerm : nonTerms)
        {
            auto node = GSS_node(nonTerm, i);
            node.SP = curId;
            ++ curId;
            GSS.emplace_back(node);
            auto findRes = nonTermStartPos.find(nonTerm);
            if (findRes != nonTermStartPos.end())
                for (auto &iter : (*findRes).second)
                {
                    workList.push(config(i, iter, node.SP));
                    history.emplace_back(config(i, iter, node.SP));
                }
        }
    }

    // stage 2: run until workList is not empty
    do
    {
        config currentConfig = workList.front();
        workList.pop();

        // situation 1: delta on terminal
        auto edgeInfoAutomation = automationEdges.find(currentConfig.curPosInAutomation);
        if (edgeInfoAutomation != automationEdges.end())
        {
            auto edgeInfoRFA = RFA_Edges.find(currentConfig.curPosInRFA);
            if (edgeInfoRFA != RFA_Edges.end())
            {
                for (auto &pairDFA : (*edgeInfoAutomation).second)
                    for (auto &pairRFA : (*edgeInfoRFA).second)
                    {
                        if (pairDFA.second == pairRFA.second)
                        {
                            addToWorkList(config(pairDFA.first, pairRFA.first, currentConfig.SP), history, workList);
                        }
                    }
            }
        }

        // situation 2: call nonterminal
        auto edgeInRFA = RFA_Edges.find(currentConfig.curPosInRFA);
        if (edgeInRFA != RFA_Edges.end())
        {
            for (auto &pairRFA : (*edgeInRFA).second)
            {
                if (isNonterminal(pairRFA.second))
                {
                    auto node = GSS_node(pairRFA.second, currentConfig.curPosInAutomation);
                    int posInGSS = addToGSS(GSS, node, curId);
                    auto findRes = findBySP(GSS, posInGSS);
                    auto addingRes = (*findRes).addEdge(pairRFA.first, currentConfig.SP);
                    for (auto &conf : addingRes)
                    {
                        // adding something is this node was popped
                        addToWorkList(conf, history, workList);
                    }

                    auto startForNonTerm = nonTermStartPos.find(pairRFA.second);
                    if (startForNonTerm != nonTermStartPos.end())
                    {
                        for (auto & start : (*startForNonTerm).second)
                        {
                            addToWorkList(config(currentConfig.curPosInAutomation, start, posInGSS), history, workList);
                        }
                    }
                }
            }
        }

        // situation 3: curPosInRFA is final to nonterm in current gss node
        auto curGSSnode = findBySP(GSS, currentConfig.SP);
        auto findEndIter = finalStatesRFA.find((*curGSSnode).nonTerm);
        // if findEndIter == end -> it is error, every nonterminal should have final
        for (auto & stateRFA : (*findEndIter).second)
        {
            if (stateRFA == currentConfig.curPosInRFA)
            {
                auto res = (*curGSSnode).pop(currentConfig.curPosInAutomation);
                for (auto &conf : res)
                {
                    addToWorkList(conf, history, workList);
                }
            }
        }

    } while ( ! workList.empty());
}

int GLL_Analysis::countResult() const
{
    int res = 0;
    for (auto &iter : GSS)
    {
        if (iter.nonTerm == "S" && iter.wasPopped)
        {
            res += iter.whereWasPopped.size();
        }
    }
    return res;
}

void GLL_Analysis::printResult(const std::string& fileName) const
{
    std::ofstream outputFile(fileName, std::ofstream::out);

    for (auto &gss_node : GSS)
    {
        if (gss_node.wasPopped)
        {
            for (auto &finalPos : gss_node.whereWasPopped)
                outputFile << "(" << gss_node.posInDFA
                           << "," << gss_node.nonTerm
                           << "," << finalPos
                           << ")" << std::endl;
        }
    }

    outputFile.close();
}

void GLL_Analysis::printResult() const
{
    for (auto &gss_node : GSS)
    {
        if (gss_node.wasPopped)
        {
            for (auto &finalPos : gss_node.whereWasPopped)
                std::cout << "(" << gss_node.posInDFA
                           << "," << gss_node.nonTerm
                           << "," << finalPos
                           << ")" << std::endl;
        }
    }
}