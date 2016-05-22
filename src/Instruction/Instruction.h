//
// Created by nicolai on 11.04.16.
//

#ifndef MINIJAVACOMPILER_INSTRUCTION_H
#define MINIJAVACOMPILER_INSTRUCTION_H

#include <string>
#include <map>
#include <memory>
#include "../IR/tree/IRTree.hpp"
#include "../frame/Temp.hpp"
#include <iostream>

namespace CodeGeneration {
    class IInstruction {
    public:
        //const char* AsmCode;
        virtual ~IInstruction() {}
        IInstruction( const std::string& text,
                      std::vector<IRTree::CTempPtr> usedVars,
                      std::vector<IRTree::CTempPtr> definedVars,
                      std::vector<IRTree::LabelPtr> jumpTargets ) :
                text(text), usedVars(usedVars), definedVars(definedVars), jumpTargets(jumpTargets) {}
        const std::vector<IRTree::CTempPtr>& UsedVars() const { return usedVars; }
        const std::vector<IRTree::CTempPtr>& DefinedVars() const { return  definedVars; }
        const std::vector<IRTree::LabelPtr>& JumpTargets() const { return jumpTargets; }
	    std::string Text() const { return text; }
        std::string Format( std::map<Temp::CTemp*, std::string>& varsMapping ) const;
	    std::string Print() const;
    protected:
        std::vector<IRTree::CTempPtr> usedVars;
        std::vector<IRTree::CTempPtr> definedVars;
        std::vector<IRTree::LabelPtr> jumpTargets;
        std::string text;
    };

    typedef std::vector<std::shared_ptr<IInstruction>> CCode ;
    typedef std::shared_ptr<IInstruction> InstructionPtr;

    void PrintCode(CCode code, std::ostream& out);

    class OPER : public IInstruction {
    public:
        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars,
              std::vector<IRTree::CTempPtr> definedVars,
              std::vector<IRTree::LabelPtr> jumpTargets ) :
                IInstruction(text, usedVars, definedVars, jumpTargets) {}

        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars,
              std::vector<IRTree::CTempPtr> definedVars ) :
                IInstruction(text, usedVars, definedVars, {}) {}

        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars ) :
                IInstruction(text, usedVars, {}, {}) {}
    };

    class LABEL : public IInstruction {
    public:
        LABEL( IRTree::LabelPtr label ) : IInstruction(label->GetName() + ":", {}, {}, {}), label(label) {}
        const IRTree::LabelPtr& Label() const { return label; }
    private:
        IRTree::LabelPtr label;
    };

    class MOVE : public IInstruction {
    public:
        MOVE( IRTree::CTempPtr from, IRTree::CTempPtr to, std::vector<IRTree::CTempPtr> definedVars )
                : IInstruction("movl %{0} %{1}", {from, to}, definedVars, {}) {}
    };
}

#endif //MINIJAVACOMPILER_INSTRUCTION_H
