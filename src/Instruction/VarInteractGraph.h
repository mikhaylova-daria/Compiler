//
// Created by nicolai on 26.04.16.
//

#ifndef MINIJAVACOMPILER_VARINTERACTGRAPH_H
#define MINIJAVACOMPILER_VARINTERACTGRAPH_H

#include "ControlFlowGraph.h"

namespace CodeGeneration {

    class CVarInteractGraph {
    public:

        CVarInteractGraph(const CControlFlowGraph& cfGraph, const std::map<Temp::CTemp*, int>& colored, int maxColors);

        struct TEdge {
            int To;
            TEdge(int to) : To(to) {}
        };
        struct TNode {
            Temp::CTemp* Var;
            std::vector<TEdge> Edges;
            std::vector<TEdge> MoveEdges;
            std::vector<int> Merged;
            bool isColored = false;
        };

        Temp::CTemp* Paint( std::vector<int>& colors );
        const std::vector<TNode>& GetNodes() const { return Nodes; }
    private:

        std::vector<bool> isDeleted;
        std::vector<int> edgesCount;
        std::vector<int> stack;

        std::set<std::pair<int, int>> nodeSet;
        std::set<std::pair<int, int>> nodeMoveSet;

        const std::map<Temp::CTemp*, int>& colored;

        std::vector<TNode> Nodes;
        std::map<Temp::CTemp*, int> VarMap;
        int k;

        void simplify();
        void coalesce();


    };

}

#endif //MINIJAVACOMPILER_VARINTERACTGRAPH_H
