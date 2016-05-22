//
// Created by nicolai on 22.05.16.
//

#ifndef MINIJAVACOMPILER_REGISTERMAPPER_H
#define MINIJAVACOMPILER_REGISTERMAPPER_H

#include <map>
#include "../frame/Temp.hpp"
#include "Instruction.h"
#include "ControlFlowGraph.h"
#include "VarInteractGraph.h"

namespace CodeGeneration {
    class CRegisterMapper {
    public:
        inline CRegisterMapper(const std::vector<Temp::CTemp *> &registers);

        inline std::map<Temp::CTemp *, Temp::CTemp *> Map(const CCode &code);

    private:
        const std::vector<Temp::CTemp *> &registers;
        std::map<Temp::CTemp*, int> colored;
    };

    std::map<Temp::CTemp *, Temp::CTemp *> CRegisterMapper::Map(const CCode &code) {
        CControlFlowGraph cfGraph(code);
        while( true ) {
            CVarInteractGraph viGraph(cfGraph, colored, static_cast<int>(registers.size()));
            std::vector<int> colors;
            Temp::CTemp* toStack = viGraph.Paint(colors);
            if( toStack != nullptr ) {
                ///
            } else {
                std::map<Temp::CTemp *, Temp::CTemp *> res;
                auto& Nodes = viGraph.GetNodes();
                for( int i = 0; i < Nodes.size(); i++ ) {
                    res[Nodes[i].Var] = registers[colors[i]];
                }
                return res;
            }
        }
    }

    CRegisterMapper::CRegisterMapper(const std::vector<Temp::CTemp *> &registers) : registers(registers) {
        for( auto& reg : registers ) {
            int color = static_cast<int>(colored.size());
            colored[reg] = color;
        }
    }
}


#endif //MINIJAVACOMPILER_REGISTERMAPPER_H
