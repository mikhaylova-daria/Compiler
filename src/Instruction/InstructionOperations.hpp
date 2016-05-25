//
// Created by Ава Катушка on 19.04.16.
//

#ifndef MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP
#define MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP

#include <vector>
#include <memory>
#include "../symbol/Symbol.h"
#include "Instruction.h"
#include <map>
#include <set>

using namespace Temp;

namespace CodeGeneration {
    using InstructionPtr = std::shared_ptr < IInstruction >;
    using CTempPtr = std::shared_ptr < CTemp >;

    class CGenerator {

        CStorage& storage;
        std::vector<CTemp*> registers;
        std::vector<CTempPtr> regHolders;

    public:

        CGenerator( CStorage& storage ) : storage( storage ) {
            std::vector<std::string> regNames = {
                    "rax", "rbx", "rcx", "rdx", "rsi", "rdi"
            };
            for( auto& name : regNames) {
                regHolders.emplace_back(new CTemp(storage.Get(name)));
                registers.push_back(regHolders.back().get());
            }
        }

        CStorage& GetStorage() { return storage; }

        const std::vector<CTemp *>& GetRegisters() { return registers; }
        const std::vector<CTempPtr>& GetRegistersPtr() { return regHolders; }
//%var1
//%var3
//%var5
//
//
//		addl %var1, %var2 // var1 - used
//		addl %var3, %var5  // var3 - used, var5 -  defined
//		addl %var2, %var5 // var5 - defined
//
//
//		movl (var1), %tmp1
//		addl %tmp1, %var2
//
//		movl (var3), %tmp2 // used
//		movl (var5), %tmp3
//		addl %tmp2, %tmp3
//		movl %tmp3, (var5) //defined
//
//movl (var5), %tmp4
//		addl %var2, %tmp4
//		movl %tmp4, (var5)

        std::vector<InstructionPtr> AddTemps(std::vector<CTemp*> &vars,
                                             CCode &instructions) {
            CCode result;
            std::set<CTemp*,Temp::CTempCompare> varsSet(vars.begin(), vars.end());

            for (auto ins: instructions) {
                //TODO: Check instruction is operation (not label)
                std::vector<CTempPtr> usedVars;

                for (auto used: ins->UsedVars()) {
                    if (varsSet.find(used.get()) != varsSet.end()) {
                        CTempPtr tempPtr = CTempPtr(new CTemp(storage));
                        InstructionPtr new_inst = InstructionPtr(new OPER("movq (<0>), <1>", {}, {used, tempPtr}, {}));
                        result.push_back(new_inst);
                        usedVars.push_back(tempPtr);
                    } else {
                        usedVars.push_back(used);
                    }
                }
                std::vector<CTempPtr> definedVars;
                //std::map<CTempPtr, CTempPtr> definedTempsToReal;
                CCode insertAfter;

                for (auto defined: ins->DefinedVars()) {
                    if (varsSet.find(defined.get()) != varsSet.end()) {
                        CTempPtr tempPtr = CTempPtr(new CTemp(storage));
                        InstructionPtr new_inst = InstructionPtr(
                                new OPER("movq {0}, (<0>)", {tempPtr}, {defined}, {}));
                        insertAfter.push_back(new_inst);
                        definedVars.push_back(tempPtr);
                        //definedTempsToReal[tempPtr] =  defined;

                    } else {
                        definedVars.push_back(defined);
                    }
                }
                //TODO: Change instruction, not create a new one
                result.emplace_back(new OPER(ins->Text(), usedVars, definedVars, ins->JumpTargets()));
                for( auto& inst : insertAfter ) {
                    result.push_back(inst);
                }
                /*
                for (auto it = definedTempsToReal.begin(); it != definedTempsToReal.end(); ++it) {
                    InstructionPtr new_inst = InstructionPtr(
                            new OPER("movq ({0}), <0>", {it->first}, {it->second}, {}));
                    result.push_back(new_inst);
                }
                */

            }
            return result;

        }
        // /* пролог */
        //  pushl %ebp              /* запоминаем текущее значение
        //                                   регистра %ebp, при этом %esp -= 4 */
        // movl  %esp, %ebp        /* записываем текущее положение
        //                                   вершины стека в %ebp              */
        //
        // /* пролог закончен, можно начинать работу */
        //
        // subl  $8, %esp          /* зарезервировать место для локальных
        //                                   переменных                        */

        std::vector<InstructionPtr> FunctionPrologue(int localVariablesCount,
                                                     std::vector<CTemp*>& usedRgisters,
                                                     std::vector<CTemp*>& argsInRegister,
                                                     std::vector<CTemp*>& mappedArgs) {
            std::vector<InstructionPtr> result;
            result.emplace_back(new OPER("pushq %rbp", {}));
            result.emplace_back(new OPER("movq %rsp, %rbp", {}));
            size_t placeForLocalVariables = localVariablesCount * sizeof(long);
            std::string reserveLocalInstruction = "subq $" + std::to_string(placeForLocalVariables) + ", %rsp";
            result.emplace_back(new OPER(reserveLocalInstruction, {}));
            for( auto& reg : usedRgisters ) {
                result.emplace_back(new OPER("pushq %" + reg->GetName(), {}));
            }
            for( int i = 0; i < argsInRegister.size(); i++) {
                if( argsInRegister[i] != nullptr ) {
                    int ind = static_cast<int>(argsInRegister.size() - i - 1);
                    std::string str = "movq " + std::to_string(16 + ind * 8) + "(%rbp), %" + mappedArgs[i]->GetName();
                    result.emplace_back(new OPER(str, {}));
                }
            }
            return result;
        }

//    /* эпилог */
//
//    movl  %ebp, %esp        /* возвращем вершину стека в исходное
//                                   положение                         */
//		    popl  %ebp              /* восстанавливаем старое значение
//                                   %ebp, при этом %esp += 4          */
//		    ret число Если команде передан операнд число, %esp увеличивается на это число.
// Это необходимо для того, чтобы подпрограмма могла убрать из стека свои параметры.


        std::vector<InstructionPtr> FunctionEpilogue(int argsCount,
                                                     std::vector<CTemp*>& usedRgisters) {
            std::vector<InstructionPtr> result;

            for( int i = usedRgisters.size() - 1; i >= 0; i--) {
                result.emplace_back(new OPER("popq %" + usedRgisters[i]->GetName(), {}));
            }

            result.emplace_back(new OPER("movq %rbp, %rsp", {}));
            result.emplace_back(new OPER("popq %rbp", {}));
            std::string argsCountStr = argsCount == 0 ? "" : "$" + std::to_string(argsCount * sizeof(long));
            result.emplace_back(new OPER("ret " + argsCountStr, {}));
            return result;
        }

        struct CFunctionGenerateArg {
            std::vector<Temp::CTempPtr> args;
            //std::vector<Temp::CTempPtr> all;
            std::set<Temp::CTemp*, Temp::CTempCompare> onStack;
            std::map<Temp::CTemp*, Temp::CTemp*, Temp::CTempCompare> tempMap;
            std::vector<Temp::CTempPtr> addedTemps;
        };

        CCode GenerateFunctionFinalCode(CCode& code, CFunctionGenerateArg& fgArg, const std::string& funcName )
        {
            std::set<CTemp*, CTempCompare> argsSet;
            std::vector<CTemp*> argsInReg;
            std::vector<CTemp*> mappedArgs;
            std::set<CTemp*, CTempCompare> usedRegsSet;
            CTempPtr rax(new CTemp(storage.Get("rax")));

            for( auto& p : fgArg.tempMap ) {
                if( *p.second != *rax.get() ) {
                    usedRegsSet.insert(p.second);
                }
            }

            std::vector<CTemp*> usedRegs(usedRegsSet.begin(), usedRegsSet.end());

            for( int i = 0; i < fgArg.args.size(); i++ ) {
                auto& arg = fgArg.args[i];
                argsSet.insert(arg.get());
                if( fgArg.onStack.find(arg.get()) == fgArg.onStack.end() ) {
                    argsInReg.push_back(arg.get());
                    mappedArgs.push_back(fgArg.tempMap[arg.get()]);
                } else {
                    argsInReg.push_back(nullptr);
                    mappedArgs.push_back(nullptr);
                    int ind = static_cast<int>(fgArg.args.size() - i - 1);
                    std::string str = std::to_string((ind) * 8 + 16) + "(%rbp)";
                    fgArg.addedTemps.emplace_back(new Temp::CTemp(storage.Get(str)));
                    fgArg.tempMap[arg.get()] = fgArg.addedTemps.back().get();
                }
            }

            int nextVarInd = 0;
            for( auto& p : fgArg.tempMap ) {
                if( fgArg.onStack.find(p.first) != fgArg.onStack.end() ) {
                    if( argsSet.find(p.first) == argsSet.end()) {
                        std::string str = std::to_string(-nextVarInd * 8) + "(%rbp)";
                        fgArg.addedTemps.emplace_back(new Temp::CTemp(storage.Get(str)));
                        p.second = fgArg.addedTemps.back().get();
                        nextVarInd++;
                    }
                }
            }

            CCode resCode;
            resCode.emplace_back(new LABEL(IRTree::LabelPtr(new Temp::CLabel(storage.Get(funcName)))));
            auto prolog = FunctionPrologue(fgArg.args.size(), usedRegs, argsInReg, mappedArgs);
            for( auto& inst : prolog ) {
                resCode.push_back(inst);
            }

            for( auto& op : code ) {
                resCode.push_back(op);
            }
            auto epilog = FunctionEpilogue(fgArg.args.size(), usedRegs);
            for( auto& inst : epilog ) {
                resCode.push_back(inst);
            }
            return resCode;

        }
    };
}


#endif //MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP
