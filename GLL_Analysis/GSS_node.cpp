//
// Created by ivan on 30/12/17.
//

#include "GSS_node.h"
#include <tuple>

GSS_node::GSS_node(std::string nonTerminal, int positionInDFA)
        : nonTerm(std::move(nonTerminal)), posInDFA(positionInDFA)
// CLion advises to pass string by value and use std::move
{
    whereWasPopped = std::vector<int>(0);
}

std::vector<config> GSS_node::addEdge(int returnPos, int SP)
{
    std::vector<config> result = std::vector<config>(0);
    for (auto &edge : edges)
    {
        if (std::get<0>(edge) == returnPos && std::get<1>(edge) == SP)
            return result;
    }

    edges.emplace_back(std::make_pair(returnPos, SP));
    // if this node was popped -> should make configs with new edge
    if (wasPopped)
    {
        for (auto & pos: whereWasPopped)
        {
            result.emplace_back(config(pos, returnPos, SP));
        }
    }

    return result;
}

std::vector<config> GSS_node::pop(int curPosInDFA)
{
    std::vector<config> result = std::vector<config>(0);
    for (auto &edge: edges)
    {
        result.emplace_back(config(curPosInDFA, std::get<0>(edge), std::get<1>(edge)));
    }
    wasPopped = true;
    for (auto &finalPos : whereWasPopped)
    {
        if (finalPos == curPosInDFA)
            return result;
    }
    whereWasPopped.push_back(curPosInDFA);

    return result;
}