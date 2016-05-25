//
// Created by nicolai on 19.04.16.
//

#ifndef MINIJAVACOMPILER_CONTROLFLOWGRAPH_H
#define MINIJAVACOMPILER_CONTROLFLOWGRAPH_H

#include <set>
#include "../frame/Temp.hpp"
#include "Instruction.h"

namespace CodeGeneration {

    class CControlFlowGraph {
    public:

        CControlFlowGraph(const std::vector<std::shared_ptr<IInstruction>> &instructions);

        struct TEdge {
            int To;
            TEdge(int to) : To(to) {}
        };
        struct TNode {
            std::set<Temp::CTemp *, Temp::CTempCompare> LiveIn;
            std::set<Temp::CTemp *, Temp::CTempCompare> LiveOut;
            std::set<Temp::CTemp *, Temp::CTempCompare> Defined;
            std::vector<TEdge> Edges;
            std::vector<TEdge> BackEdges;
            std::shared_ptr<IInstruction> Instruct;
        };

        std::vector<TNode> Nodes;

        void Dump(std::ostream& out);

    private:
        void process();
    };

}

#endif //MINIJAVACOMPILER_CONTROLFLOWGRAPH_H
