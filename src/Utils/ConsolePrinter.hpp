//
// Created by Ава Катушка on 07.11.15.
//

#ifndef MINIJAVACOMPILER_CONSOLEPRINTER_HPP
#define MINIJAVACOMPILER_CONSOLEPRINTER_HPP

#include "../tree/MinijavaTree.h"


class ConsolePrinter {

public:
    static void print( const std::string& what ) {
	    std::cout << what;
    }

    static void printTab() {
	    std::cout << "  ";
    }

    static void printNewLine() {
        std::cout << "\n";
    }

    static void print(TType type) {
		switch (type) {
			case T_INT :
				print("INT");
				break;
			case T_BOOL :
				print("BOOL");
				break;
			case T_INT_ARRAY :
				print("INT_ARRAY");
				break;
			case T_CLASS :
				print("CLASS");
				break;
			default:
				assert(false);
		}
    }

    static void print(TBinaryExpression type) {
	    switch(type) {
		    case BE_PLUS : {
			    print( "BE_PLUS" );
			    break;
		    }
		    case BE_MINUS : {
			    print( "BE_MINUS" );
			    break;
		    }
		    case BE_MULTIPLICATION: {
			    print( "BE_MULTIPLICATION" );
			    break;
		    }
		    case BE_LESS: {
			    print( "BE_LESS" );
			    break;
		    }
		    case BE_AND: {
			    print( "BE_AND" );
			    break;
		    }
		    case BE_EQUAL: {
			    print( "BE_EQUAL" );
			    break;
		    }
		    case BE_SQ_BRACKETS: {
			    print("BE_SQ_BRACKETS");
			    break;
		    }
		    default:{
			    print("BE_UNRECOGNISED");
			    break;
		    }
	    }
    }

};




#endif //MINIJAVACOMPILER_CONSOLEPRINTER_HPP
