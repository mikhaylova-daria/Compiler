//
// Created by Ава Катушка on 12.04.16.
//
#include <map>

namespace CodeGeneration {
    void IInstruction::Print() const {
	    std::map < Temp::CTemp*, std::string > varsMapping;
	    for ( auto var : usedVars ) {
		    varsMapping.emplace( var.get(), var->GetName());
	    }
	    for ( auto var : definedVars ) {
		    varsMapping.emplace( var.get(), var->GetName());
	    }
	    return Format( varsMapping );
    }
}