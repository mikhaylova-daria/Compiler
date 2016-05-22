//
// Created by Ава Катушка on 19.04.16.
//

#ifndef MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP
#define MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP

#include <vector>
#include <memory>
#include "../symbol/Symbol.h"
#include <map>

using InstructionPtr = std::shared_ptr < IInstruction >;
using CTempPtr = std::shared_ptr < CTemp >;

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

std::vector < InstructionPtr > AddTemps( std::vector < CTempPtr >& vars, std::vector < InstructionPtr >& instructions,
                                         CStorage& storage ) {
	std::vector < InstructionPtr > result;
	std::set < CTempPtr > varsSet( vars.begin(), vars.end());

	for ( auto ins: instructions ) {
		//TODO: Check instruction is operation (not label)
		std::vector <CTempPtr> usedVars;

		for ( auto used: ins.UsedVars()) {
			if ( varsSet.find( used ) != varsSet.end()) {
				CTempPtr tempPtr = CTempPtr( new CTemp( storage ));
				InstructionPtr new_inst = InstructionPtr( new OPER( "movl ({0}) <0>", { used }, { tempPtr }, { } ));
				result.push_back( new_inst );
				usedVars.push_back( tempPtr );
			} else {
				usedVars.push_back(used);
			}
		}
		std::vector <CTempPtr> definedVars;
		std::map <CTempPtr, CTempPtr> definedTempsToReal;

		for ( auto defined: ins.DefinedVars()) {
			if ( varsSet.find( defined ) != varsSet.end()) {
				CTempPtr tempPtr = CTempPtr( new CTemp( storage ));
				InstructionPtr new_inst = InstructionPtr( new OPER( "movl ({0}) <0>", { defined }, { tempPtr }, { } ));
				result.push_back( new_inst );
				definedVars.push_back( tempPtr );
				definedTempsToReal.emplace({tempPtr, defined});

			} else {
				definedVars.push_back(defined);
			}
		}
		//TODO: Change instruction, not create a new one
		result.push_back( new OPER( ins.Text(), usedVars, definedVars, ins.JumpTargets()));

		for (auto it = definedTempsToReal.begin(); it != definedTempsToReal.end(); ++it) {
			InstructionPtr new_inst = InstructionPtr(
					new OPER( "movl ({0}) <0>", { it->first }, { it->second }, { } ));
			result.push_back( new_inst );
		}

	}

}

#endif //MINIJAVACOMPILER_INSTRUCTIONOPERATIONS_HPP
