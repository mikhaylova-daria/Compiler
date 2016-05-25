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
#include "InstructionOperations.hpp"

namespace CodeGeneration {
    class CRegisterMapper {
    public:
        inline CRegisterMapper(CGenerator& generator);

        struct MapResult {
            std::map<Temp::CTemp*, Temp::CTemp*, Temp::CTempCompare> TempToReg;
            std::vector<Temp::CTemp*> OnStack;
            std::vector<Temp::CTemp*> ArgsInReg;
            CCode Code;
        };

        inline MapResult Map(const CCode &code, const std::vector<Temp::CTemp*>& args );

    private:
        const std::vector<Temp::CTemp *> &registers;
        CGenerator& generator;
        std::map<Temp::CTemp*, int, Temp::CTempCompare> colored;
        Temp::CTempPtr fictReg;
    };

    CRegisterMapper::MapResult CRegisterMapper::Map(const CCode &code, const std::vector<Temp::CTemp*>& args ) {
        CCode nextCode = code;
        std::set<Temp::CTemp*> argSet( args.begin(), args.end() );
        std::map<Temp::CTemp*, int, Temp::CTempCompare> currColored = colored;
        MapResult res;
        std::vector<Temp::CTemp*> argsOnStack;
        int logNum = 0;
        while( true ) {
            CControlFlowGraph cfGraph(nextCode);
            std::ofstream out("cf_graph_" + std::to_string(logNum) + ".gv");
            cfGraph.Dump(out);
            std::ofstream out2("vi_graph_" + std::to_string(logNum) + ".gv");
            CVarInteractGraph viGraph(cfGraph, currColored, static_cast<int>(registers.size()), generator.GetStorage());
            viGraph.Dump(out2);
            std::vector<int> colors;
            Temp::CTemp* toStack = viGraph.Paint(colors);
            if( toStack != nullptr ) {
                std::cout << "to stack: " << toStack->GetName() << std::endl;
                std::vector<Temp::CTemp*> toStackVec = { toStack };
                nextCode = generator.AddTemps(toStackVec, nextCode );
                res.OnStack.push_back(toStack);
                if( argSet.find(toStack) != argSet.end()) {
                    argsOnStack.push_back(toStack);
                }
                currColored[toStack] = registers.size();
            } else {
                auto& Nodes = viGraph.GetNodes();
                for( int i = 0; i < Nodes.size(); i++ ) {
                    if( colors[i] < registers.size() ) {
                        res.TempToReg[Nodes[i].Var] = registers[colors[i]];
                    } else {
                        res.TempToReg[Nodes[i].Var] = fictReg.get();
                    }
                }
                for( auto& arg : argsOnStack ) {
                    argSet.erase(arg);
                }
                res.ArgsInReg.assign(argSet.begin(), argSet.end());
                res.Code = nextCode;
                return res;
            }
        }
    }

    CRegisterMapper::CRegisterMapper(CGenerator& generator)
            : registers(generator.GetRegisters()), generator(generator) {
        for( auto& reg : registers ) {
            int color = static_cast<int>(colored.size());
            colored[reg] = color;
        }
        fictReg = CTempPtr(new Temp::CTemp(generator.GetStorage().Get("fictReg")));
    }
}


#endif //MINIJAVACOMPILER_REGISTERMAPPER_H
