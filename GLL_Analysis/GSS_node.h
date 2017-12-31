//
// Created by ivan on 30/12/17.
//

#ifndef GRAMMARANALYSIS_GSS_NODE_H
#define GRAMMARANALYSIS_GSS_NODE_H

#include <string>
#include <vector>

// first int - pos in RFA, second - id of another node
using edgesType = std::vector<std::pair<int, int>>;

struct config
{
    int curPosInAutomation;
    int curPosInRFA;
    int SP;

    explicit config(int curPosDFA = 0, int curGrm = 0, int stackPointer = 0)
            : curPosInAutomation(curPosDFA), curPosInRFA(curGrm), SP(stackPointer)
    {}

    bool operator==(const config& rhs)
    {
        return (curPosInRFA == rhs.curPosInRFA && curPosInAutomation == rhs.curPosInAutomation && SP == rhs.SP);
    }

    bool operator!=(const config& rhs)
    {
        return ! (*this == rhs);
    }
};

class GSS_node
{
public:
    const std::string nonTerm;
    const int posInDFA;
    bool wasPopped = false;
    int SP;
    edgesType edges;
    std::vector<int> whereWasPopped;

    GSS_node(std::string nonTerminal, int positionInDFA);
    // return true, if edge did not exist -> add it
    std::vector<config> addEdge(int returnPos, int SP);

    std::vector<config> pop(int curPosInDFA);
};


#endif //GRAMMARANALYSIS_GSS_NODE_H
