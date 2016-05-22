//
// Created by nicolai on 19.04.16.
//


#include "ControlFlowGraph.h"

#include <map>

namespace CodeGeneration {

    CControlFlowGraph::CControlFlowGraph(const std::vector<std::shared_ptr<CodeGeneration::IInstruction>> &instructions) {
        std::map<Temp::CLabel*, int> labels;
        for( int i = 0; i < instructions.size(); i++) {
            LABEL* label = dynamic_cast<LABEL*>(instructions[i].get());
            if( label != nullptr ) {
                labels[label->Label().get()] = i;
            }
        }
        Nodes.assign(instructions.size(), TNode());
        for( int i = 0; i < instructions.size();i++) {
            Nodes[i].Instruct = instructions[i];
            for( auto& l : instructions[i]->JumpTargets()) {
                Nodes[i].Edges.push_back(TEdge(labels[l.get()]));
                Nodes[Nodes[i].Edges.back().To].Edges.push_back(TEdge(i));
            }
            if( i + 1 < instructions.size()) {
                Nodes[i].Edges.push_back(TEdge(i + 1));
                Nodes[i + 1].BackEdges.push_back(TEdge(i));
            }
            auto& usedVars = instructions[i]->UsedVars();
            auto& definedVars = instructions[i]->DefinedVars();
            Nodes[i].LiveIn.insert(usedVars.begin(), usedVars.end());
            Nodes[i].Defined.insert(definedVars.begin(), definedVars.end());
        }
    }

    void CControlFlowGraph::process() {
        std::set<int> toUpdate;
        for( int i = 0; i < Nodes.size(); i++) {
            toUpdate.insert(i);
        }
        while( !toUpdate.empty()) {
            int node = *toUpdate.begin();
            toUpdate.erase(toUpdate.begin());
            for( auto& out : Nodes[node].LiveOut) {
                if( Nodes[node].Defined.find(out) == Nodes[node].Defined.end()) {
                    Nodes[node].LiveIn.insert(out);
                }
            }
            for( auto& in : Nodes[node].LiveIn) {
                for( auto& edge: Nodes[node].BackEdges) {
                    if( Nodes[edge.To].LiveOut.find(in) == Nodes[edge.To].LiveOut.end()) {
                        Nodes[edge.To].LiveOut.insert(in);
                        toUpdate.insert(edge.To);
                    }
                }
            }
        }
    }
}


