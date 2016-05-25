//
// Created by nicolai on 26.04.16.
//

#include "VarInteractGraph.h"

namespace CodeGeneration {

    CVarInteractGraph::CVarInteractGraph(const CControlFlowGraph &cfGraph,
                                         const std::map<Temp::CTemp*, int, Temp::CTempCompare>& colored,
                                         int maxColors,
                                         CStorage& storage) :
            k(maxColors), colored(colored), storage(storage) {
        std::set<Temp::CTemp*,Temp::CTempCompare> nodes;
        for( auto& node : cfGraph.Nodes) {
            nodes.insert(node.LiveOut.begin(), node.LiveOut.end());
            nodes.insert(node.LiveIn.begin(), node.LiveIn.end());
            nodes.insert(node.Defined.begin(), node.Defined.end());
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
            bool isMove = dynamic_cast<MOVE*>(node.Instruct.get()) != nullptr;
            auto& usedVars = node.Instruct->UsedVars();
            int escape = isMove ? VarMap[usedVars[0].get()] : -1;
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
            if( pair.first != pair.second ) {
                Nodes[pair.first].Edges.push_back(TEdge(pair.second));
            }
        }
    }

    void CVarInteractGraph::simplify() {
        while( true ) {
            dump();
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
            int toStack = Nodes[node].Merged.empty() ? node : Nodes[node].Merged[0];
            stack.push_back(toStack);
            isDeleted[node] = true;
            for( auto& edge : Nodes[node].Edges ) {
                auto iter1 = nodeMoveSet.find({edgesCount[edge.To], edge.To});
                auto iter2 = nodeSet.find({edgesCount[edge.To], edge.To});
                edgesCount[edge.To]--;
                if( iter1 != nodeMoveSet.end() ) {
                    nodeMoveSet.erase(iter1);
                    nodeMoveSet.insert({edgesCount[edge.To], edge.To});
                }
                if( iter2 != nodeSet.end() ) {
                    nodeSet.erase(iter2);
                    nodeSet.insert({edgesCount[edge.To], edge.To});
                }
            }
        }
    }

    void CVarInteractGraph::coalesce() {
        //dump();
        for( auto p : nodeMoveSet ) {
            int node = p.second;
            assert(!isDeleted[node]);
            for( auto& edge : Nodes[node].MoveEdges ) {
                bool skip = isDeleted[edge.To] || (Nodes[node].isColored && Nodes[edge.To].isColored);
                if( !skip && edgesCount[node] + edgesCount[edge.To] < k) {
                    // merge node and edge.To

                    merge(node, edge.To);
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
                colors[i] = colored.find(Nodes[i].Var)->second;
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
                    for( auto to : Nodes[next].Merged ) {
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
                            usedColors[colors[edge.To]] = true;
                        }
                    }
                }

                int color = -1;
                for( int next : merged ) {
                    if( isColored[next] ) {
                        assert(color == -1 || colors[next] == color);
                        color = colors[next];
                    }
                }

                for( int i = 0; i < usedColors.size() && color == -1; i++ ) {
                    if( !usedColors[i] ) {
                        color = i;
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

    void CVarInteractGraph::merge(int from, int to) {
        int next = static_cast<int>(Nodes.size());
        Nodes.push_back(TNode());
        TNode& nextNode = Nodes.back();
        TNode& fromNode = Nodes[from];
        TNode& toNode = Nodes[to];

        Temp::CTempPtr var( new Temp::CTemp(storage.Get(fromNode.Var->GetName() + " + " + toNode.Var->GetName())));

        nextNode.Var = var.get();
        nextNode.isColored = fromNode.isColored || toNode.isColored;

        std::vector<bool> hasEdge(Nodes.size(), false);
        std::vector<bool> hasMoveEdge(Nodes.size(), false);

        for( auto& edge : fromNode.Edges ) {
            if( isDeleted[edge.To]) {
                continue;
            }
            hasEdge[edge.To] = true;
            nextNode.Edges.push_back(edge);
            Nodes[edge.To].Edges.push_back(TEdge(next));
        }

        for(auto& edge : toNode.Edges) {
            if( isDeleted[edge.To]) {
                continue;
            }
            if( !hasEdge[edge.To] ) {
                hasEdge[edge.To] = true;
                nextNode.Edges.push_back(edge);
                Nodes[edge.To].Edges.push_back(TEdge(next));
            } else {
                nodeSet.erase({edgesCount[edge.To], edge.To});
                nodeMoveSet.erase({edgesCount[edge.To], edge.To});
                edgesCount[edge.To]--;
                if( Nodes[edge.To].MoveEdges.size() == 0) {
                    nodeSet.insert({edgesCount[edge.To], edge.To});
                } else {
                    nodeMoveSet.insert({edgesCount[edge.To], edge.To});
                }
            }
        }

        for( auto& edge : fromNode.MoveEdges ) {
            if( isDeleted[edge.To]) {
                continue;
            }
            if( !hasEdge[edge.To] && !edge.To == to ) {
                hasMoveEdge[edge.To] = true;
                nextNode.MoveEdges.push_back(edge);
                Nodes[edge.To].MoveEdges.push_back(TEdge(next));
            }
        }

        for(auto& edge : toNode.MoveEdges) {
            if( isDeleted[edge.To]) {
                continue;
            }
            if( !hasEdge[edge.To] && !hasMoveEdge[edge.To] && !edge.To == from ) {
                hasMoveEdge[edge.To] = true;
                nextNode.MoveEdges.push_back(edge);
                Nodes[edge.To].MoveEdges.push_back(TEdge(next));
            }
        }

        isDeleted[from] = true;
        isDeleted[to] = true;
        nodeSet.erase({edgesCount[from], from});
        nodeSet.erase({edgesCount[to], to});
        nodeMoveSet.erase({edgesCount[from], from});
        nodeMoveSet.erase({edgesCount[to], to});
        int fromMerge = fromNode.Merged.empty() ? from : fromNode.Merged[0];
        int toMerge = toNode.Merged.empty() ? to : toNode.Merged[0];
        Nodes[fromMerge].Merged.push_back(toMerge);
        Nodes[toMerge].Merged.push_back(fromMerge);
        nextNode.Merged.push_back(fromMerge);
        nextNode.Merged.push_back(to);

        isDeleted.push_back(false);
        edgesCount.push_back(nextNode.Edges.size());

        if( nextNode.MoveEdges.empty() ) {
            nodeSet.insert({edgesCount[next], next});
        } else {
            nodeMoveSet.insert({edgesCount[next], next});
        }

        simplify();

        for( auto& edge : Nodes[next].Edges ) {
            Nodes[edge.To].Edges.pop_back();
        }
        for( auto& edge : Nodes[next].MoveEdges ) {
            Nodes[edge.To].MoveEdges.pop_back();
        }
        Nodes.pop_back();
    }

    void CVarInteractGraph::Dump(std::ostream &out) {
        out << "digraph {" << std::endl;
        out << "concentrate=true" << std::endl;
        for( int i = 0; i < Nodes.size(); i++) {
            if( isDeleted.size() == 0 || !isDeleted[i] ) {
                out << i << "[label=\"" << Nodes[i].Var->GetName() << " (" << i << ")\"]" << std::endl;
            }
        }
        for( int i = 0; i < Nodes.size(); i++) {
            if( isDeleted.size() == 0 || !isDeleted[i] ) {
                for (auto &edge : Nodes[i].Edges) {
                    out << i << " -> " << edge.To << "[arrowhead=none]" << ";" << std::endl;
                }
            }
        }
        for( int i = 0; i < Nodes.size(); i++) {
            if( isDeleted.size() == 0 || !isDeleted[i] ) {
                for (auto &edge : Nodes[i].MoveEdges) {
                    out << i << " -> " << edge.To << "[arrowhead=none,style=dotted]" << ";" << std::endl;
                }
            }
        }
        out << "}\n";
    }
}

