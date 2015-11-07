//
// Created by Ава Катушка on 07.11.15.
//

#ifndef MINIJAVACOMPILER_CONSOLEPRINTER_HPP
#define MINIJAVACOMPILER_CONSOLEPRINTER_HPP

#include "../tree/MinijavaTree.h"


class ConsolePrinter {

public:
    static void print( const std::string& what ) {
	    std::cout << what << std::endl;
    }

    static void printTab() {
	    std::cout << "  ";
    }

    static void print(TConstantType type) {
	    if (type == TConstantType::CT_INT) {
		    print("INT");
	    } else if (type == TConstantType::CT_BOOL) {
		    print("BOOL");
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
