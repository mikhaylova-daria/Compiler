//
// Created by nicolai on 26.04.16.
//

#include "VarInteractGraph.h"

namespace CodeGeneration {

    CVarInteractGraph::CVarInteractGraph(const CControlFlowGraph &cfGraph,
                                         const std::map<Temp::CTemp*, int>& colored,
                                         int maxColors) :
            k(maxColors), colored(colored) {
        std::set<Temp::CTemp*> nodes;
        for( auto& node : cfGraph.Nodes) {
            nodes.insert(node.LiveOut.begin(), node.LiveOut.end());
            nodes.insert(node.LiveIn.begin(), node.LiveIn.end());
        }
        for( auto& node: nodes) {
            int ind = static_cast<int>(Nodes.size());
            Nodes.push_back(TNode());
            Nodes[ind].Var = node;
            Nodes[ind].isColored = colored.find(node) != colored.end();
            VarMap[node] = ind;
        }
        std::set<std::pair<int,int>> edges;
        for( auto& node: cfGraph.Nodes ) {
            bool isMove = dynamic_cast<MOVE*>(node.Instruct.get()) == nullptr;
            int escape = isMove ? VarMap[node.Instruct->UsedVars()[0].get()] : -1;
            for( auto& def : node.Defined ) {
                int defInd = VarMap[def];
                for (auto out : node.LiveOut) {
                    int outInd = VarMap[out];
                    if( outInd != escape ) {
                        edges.insert(std::make_pair(defInd, outInd));
                        edges.insert(std::make_pair(outInd, defInd));
                    }
                }
            }
        }
        for( auto& node: cfGraph.Nodes ) {
            auto move = dynamic_cast<MOVE*>(node.Instruct.get());
            if( move != nullptr ) {
                int from = VarMap[move->UsedVars()[0].get()];
                int to = VarMap[move->DefinedVars()[0].get()];
                //Nodes[from].isMoveArg = Nodes[to].isMoveArg = true;
                if( edges.find({from, to}) == edges.end()) {
                    Nodes[from].MoveEdges.push_back(TEdge(to));
                    Nodes[to].MoveEdges.push_back(TEdge(from));
                }
            }
        }
        for( auto& pair : edges) {
            Nodes[pair.first].Edges.push_back(TEdge(pair.second));
        }
    }

    void CVarInteractGraph::simplify() {
        while( true ) {
            if( nodeSet.empty() && nodeMoveSet.empty() ) {
                break;
            }
            if( nodeSet.empty() || nodeSet.begin()->first > k) {
                coalesce();
                if( nodeSet.empty() ) {
                    if( nodeMoveSet.empty() ) {
                        break;
                    } else {
                        // freeze (possible spill)
                        nodeSet.insert(*nodeMoveSet.begin());
                        nodeMoveSet.erase(nodeMoveSet.begin());
                    }
                } else {
                    if( nodeSet.begin()->first > k ) {
                        if( !nodeMoveSet.empty() && nodeMoveSet.begin()->first <= k) {
                            // freeze
                            nodeSet.insert(*nodeMoveSet.begin());
                            nodeMoveSet.erase(nodeMoveSet.begin());
                        }
                        // else spill
                    }
                    // else spill
                }
            }
            int node = nodeSet.begin()->second;
            nodeSet.erase(nodeSet.begin());
            stack.push_back(node);
            isDeleted[node] = true;
            for( auto& edge : Nodes[node].Edges ) {
                edgesCount[edge.To]--;
            }
        }
    }

    void CVarInteractGraph::coalesce() {
        for( auto p : nodeMoveSet ) {
            int node = p.second;
            for( auto& edge : Nodes[node].MoveEdges ) {
                bool skip = isDeleted[edge.To] || (Nodes[node].isColored && Nodes[edge.To].isColored);
                if( !skip && edgesCount[node] + edgesCount[edge.To] < k) {
                    // merge node and edge.To
                    nodeMoveSet.erase(nodeMoveSet.begin());
                    nodeMoveSet.erase({edgesCount[edge.To], edge.To});
                    isDeleted[edge.To] = true;
                    TNode oldNode;
                    std::vector<int> decreased;
                    std::swap(oldNode, Nodes[node]);
                    {
                        std::set<int> nodeEdges;
                        std::set<int> toEdges;
                        std::set<int> nodeMoveEdges;
                        std::set<int> toMoveEdges;
                        for (auto &e : oldNode.Edges) {
                            if (!isDeleted[e.To]) {
                                nodeEdges.insert(e.To);
                            }
                        }
                        for (auto &e : oldNode.MoveEdges) {
                            if (!isDeleted[e.To] && e.To != edge.To) {
                                nodeMoveEdges.insert(e.To);
                            }
                        }
                        for (auto &e : Nodes[edge.To].Edges) {
                            if (!isDeleted[e.To]) {
                                toEdges.insert(e.To);
                            }
                        }
                        for (auto &e : Nodes[edge.To].MoveEdges) {
                            if (!isDeleted[e.To]) {
                                toMoveEdges.insert(e.To);
                            }
                        }

                        for( auto& e : nodeEdges ) {
                            if( toEdges.find(e) != toEdges.end()) {
                                decreased.push_back(e);
                            }
                        }

                        std::set<int> commEdges(nodeEdges);
                        commEdges.insert(toEdges.begin(), toEdges.end());
                        std::set<int> commMoveEdges(nodeMoveEdges);
                        commMoveEdges.insert(toMoveEdges.begin(), toMoveEdges.end());
                        commEdges.erase(node);
                        commEdges.erase(edge.To);
                        commEdges.erase(commEdges.begin(), commEdges.end());
                        Nodes[node].Edges.assign(commEdges.begin(), commEdges.end());
                        Nodes[node].MoveEdges.assign(commMoveEdges.begin(), commMoveEdges.end());
                    }
                    for( auto& e : Nodes[edge.To].Edges ) {
                        Nodes[e.To].Edges.push_back(node);
                    }
                    for( auto& e : Nodes[node].MoveEdges ) {
                        Nodes[e.To].MoveEdges.push_back(node);
                    }

                    Nodes[node].isColored = oldNode.isColored || Nodes[edge.To].isColored;

                    simplify();

                    for( auto& e : Nodes[edge.To].Edges ) {
                        Nodes[e.To].Edges.pop_back();
                    }
                    for( auto& e : Nodes[node].MoveEdges ) {
                        Nodes[e.To].MoveEdges.pop_back();
                    }
                    Nodes[node] = oldNode;
                    Nodes[node].Merged.push_back(edge.To);
                    Nodes[edge.To].Merged.push_back(node);
                    return;
                }
            }
        }
    }

    Temp::CTemp* CVarInteractGraph::Paint(std::vector<int> &colors) {
        isDeleted.assign( Nodes.size(), false );
        edgesCount.resize( Nodes.size() );
        for( int i = 0; i < Nodes.size(); i++ ) {
            edgesCount[i] = static_cast<int>(Nodes[i].Edges.size());
            if( !Nodes[i].isColored) {
                auto &set = Nodes[i].MoveEdges.size() == 0 ? nodeSet : nodeMoveSet;
                set.insert({edgesCount[i], i});
            }
        }
        simplify();

        colors.resize( Nodes.size() );
        std::vector<bool> isColored(colors.size(), false);
        for( int i = 0; i < Nodes.size(); i++ ) {
            if( Nodes[i].isColored ) {
                isColored[i] = true;
                colors[i] = colored[Nodes[i].Var];
            }
        }
        while( !stack.empty() ) {
            int node = stack.back();
            stack.pop_back();
            if( !isColored[node] ) {

                std::set<int> merged;
                std::vector<int> toVisit;
                toVisit.push_back(node);
                merged.insert(node);
                while( !toVisit.empty()) {
                    int next = toVisit.back();
                    toVisit.pop_back();
                    for( auto& to : Nodes[next].Merged ) {
                        if( merged.find(to) == merged.end() ) {
                            merged.insert(to);
                            toVisit.push_back(to);
                        }
                    }
                }

                std::vector<bool> usedColors(k, false);
                for( int next : merged) {
                    for( auto& edge : Nodes[next].Edges ) {
                        if( isColored[edge.To] ) {
                            usedColors[edge.To] = true;
                        }
                    }
                }

                int color = -1;
                for( int i = 0; i < usedColors.size(); i++ ) {
                    if( !usedColors[i] ) {
                        color = i;
                        break;
                    }
                }

                if( color == -1 ) {
                    return Nodes[node].Var;
                }

                for( int next : merged) {
                    colors[next] = color;
                    isColored[next] = true;
                }
            }
        }
        return nullptr;
    }
}

