//
// Created by Ава Катушка on 12.04.16.
//
#include <map>
#include "Instruction.h"

namespace CodeGeneration {
    std::string IInstruction::Print() const {
	    std::map<Temp::CTemp*, std::string, Temp::CTempCompare> varsMapping;
	    for ( auto var : usedVars ) {
		    varsMapping.emplace( var.get(), var->GetName());
	    }
	    for ( auto var : definedVars ) {
		    varsMapping.emplace( var.get(), var->GetName());
	    }
	    return Format( varsMapping );
    }

	void PrintCode(const CCode& code, std::ostream& out) {
		for (auto instraction: code) {
			out << instraction->Print() << std::endl;
		}
	}

	void PrintCode(const CCode& code, std::ostream& out, std::map<Temp::CTemp*,Temp::CTemp*,Temp::CTempCompare>& map ) {
		std::map <Temp::CTemp*, std::string,Temp::CTempCompare> varsMapping;
		for( auto& p : map) {
			varsMapping[p.first] = p.second->GetName();
		}
		for( auto& instruction : code ) {
			MOVE* move = dynamic_cast<MOVE*>(instruction.get());
            if( move != nullptr ) {
                if( *map[move->UsedVars()[0].get()] == *map[move->DefinedVars()[0].get()]) {
                    continue;
                }
            }
			out << instruction->Format(varsMapping) << std::endl;
		}
	}

	std::string IInstruction::Format(std::map<Temp::CTemp*, std::string, Temp::CTempCompare>& varsMapping) const {
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
					//auto &vars = (text[i] == '}' ? usedVars : definedVars);
                    Temp::CTemp* tmp = (text[i] == '}' ? usedVars[val].get() : definedVars[val].get());
					result += varsMapping[tmp];
				}
				lastOpened = -1;
			} else if(lastOpened < 0) {
				result += text[i];
			}
		}
		return result;
	}
}