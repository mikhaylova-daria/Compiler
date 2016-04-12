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

namespace CodeGeneration {
    class IInstruction {
        //const char* AsmCode;
        virtual ~IInstruction() {}
        const std::vector<IRTree::CTempPtr>& UsedVars() const { return usedVars; }
        const std::vector<IRTree::CTempPtr>& definedVars() const { return  definedVars; }
        const std::vector<IRTree::LabelPtr>& JumpTargets() const { return jumpTargets; }
        std::string Format( const std::map<Temp::CTemp*, std::string>& varsMapping ) const;
	    std::string Print() const;
    protected:
        std::vector<IRTree::CTempPtr> usedVars;
        std::vector<IRTree::CTempPtr> definedVars;
        std::vector<IRTree::LabelPtr> jumpTargets;
        std::string text;
    };

    typedef std::vector<std::shared_ptr<IInstruction>> CCode ;

	void PrintCode(CCode code) {
		for (auto instraction: code) {
			cout << instraction->Print() << endl;
		}
	}

    class OPER : public IInstruction {
    public:
        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars,
              std::vector<IRTree::CTempPtr> definedVars,
              std::vector<IRTree::LabelPtr> jumpTargets ) :
                text(text), usedVars(usedVars), definedVars(definedVars), jumpTargets(jumpTargets) {}

        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars,
              std::vector<IRTree::CTempPtr> definedVars ) :
                text(text), usedVars(usedVars), definedVars(definedVars) {}

        OPER( const std::string& text,
              std::vector<IRTree::CTempPtr> usedVars ) :
                text(text), usedVars(usedVars) {}
    };

    class LABEL : public IInstruction {
    public:
        LABEL( IRTree::LabelPtr label ) : text(label->GetName() + ":") {}
    };

    class MOVE : public IInstruction {
    public:
        MOVE( IRTree::CTempPtr from, IRTree::CTempPtr to, std::vector<IRTree::CTempPtr> definedVars )
                : usedVars({from, to}), text("movl %{0} %{1}"), definedVars(definedVars) {}
    };

    std::string IInstruction::Format(const std::map<Temp::CTemp*, std::string>& varsMapping) const {
        int lastOpened = -1;
        std::string result;
        for( int i = 0; i < text.size(); i++) {
            if( text[i] == '{' || text[i] == '<' || text[i] == '[') {
                lastOpened = i;
            } else if((text[i] == '}' || text[i] == '>' || text[i] == ']') && lastOpened >= 0) {
                std::string substr = text.substr(lastOpened + 1, i - lastOpened - 1);
                int val = std::stoi(substr);
                if( text[i] == ']') {
                    result += jumpTargets[val]->GetName();
                } else {
                    auto &vars = text[i] == '}' ? usedVars : definedVars;
                    result += varsMapping[vars[i].get()];
                }
                lastOpened = -1;
            } else if(lastOpened < 0) {
                result += text[i];
            }
        }
        return result;
    }
}

#endif //MINIJAVACOMPILER_INSTRUCTION_H
