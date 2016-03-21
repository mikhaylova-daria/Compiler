//
// Created by Ава Катушка on 01.12.15.
//

#ifndef MINIJAVACOMPILER_CIRTREEPRINTER_HPP
#define MINIJAVACOMPILER_CIRTREEPRINTER_HPP

#include <fstream>
#include "IIRTreeVisitor.hpp"
#include "../../Utils/ConsolePrinter.hpp"
#include "../../IR/tree/Statements.hpp"

namespace IRTree {

    class CIRTreePrinter : public IIRTreeVisitor {
        std::ofstream tree_file;

    public:
	    CIRTreePrinter() {
		    tree_file.open ("tree.txt");
		    tree_file << "digraph {" << std::endl;

	    }

	    void printConnection(int parent, int child) {
		    tree_file << parent << " -> " << child << ";" << std::endl;
	    }

	    void defineName(std::string name, int id) {
		    tree_file << id << "[label=\"" << name << "(" << id << ")\"]" << std::endl;
	    }

	    virtual ~CIRTreePrinter() {
		    tree_file << "} " << std::endl;
		    tree_file.close();
	    }

        virtual void Visit( const MoveStatement* moveStatement );

        virtual void Visit( const ExpressionStatement* expressionStatement );

        virtual void Visit( const JumpStatement* jumpStatement );

        virtual void Visit( const CJumpStatement* cJumpStatement );

        virtual void Visit( const SEQStatement* seqStatement );

        virtual void Visit( const StatementList* statementList );

        virtual void Visit( const LabelStatement* labelStatement );

        virtual void Visit( const ConstExp* constExp );

        virtual void Visit( const PlatformConstExp* platformConstExp );

        virtual void Visit( const NameExp* nameExp );

        virtual void Visit( const TempExp* tempExp );

        virtual void Visit( const BinopExp* binopExp );

        virtual void Visit( const MemExp* memExp );

        virtual void Visit( const ExpList* expList );

        virtual void Visit( const CallExp* callExp );

        virtual void Visit( const ESEQExp* eseqExp );

        void print( const std::string& what ) {
	        printTabs();
	        ConsolePrinter::print( what );
	        ConsolePrinter::printNewLine();
        }

        void printTabs() {
	        for ( int i = 0; i < treeDeep; i++ ) {
		        ConsolePrinter::printTab();
	        }
        }

        void print( const CJUMP& op ) {
	        switch ( op ) {
		        case CJUMP::J_EQ: {
			        print( "EQ" );
			        break;
		        }
		        case CJUMP::J_NE: {
			        print( "NE" );
			        break;
		        }
		        case CJUMP::J_LT: {
			        print( "LT" );
			        break;
		        }
		        case CJUMP::J_GE: {
			        print( "GE" );
			        break;
		        }
		        case CJUMP::J_ULT: {
			        print( "ULT" );
			        break;
		        }
		        case CJUMP::J_ULE: {
			        print( "ULE" );
			        break;
		        }
		        case CJUMP::J_UGT: {
			        print( "UGT" );
			        break;
		        }
		        case CJUMP::J_UGE: {
			        print( "UGE" );
			        break;
		        }
		        case CJUMP::J_COUNT: {
			        print( "COUNT" );
			        break;
		        }
		        case CJUMP::J_GT: {
			        print( "GT" );
			        break;
		        }
		        case CJUMP::J_LE: {
			        print( "LE" );
			        break;
		        }
	        }
        }


        void print( const BINOP& op ) {
	        switch ( op ) {
		        case PLUS: {
			        print( "PLUS" );
			        break;
		        };
		        case MINUS: {
			        print( "MINUS" );
			        break;
		        };;
		        case MUL: {
			        print( "MUL" );
			        break;
		        };;
		        case DIV: {
			        print( "DIV" );
			        break;
		        };;
		        case AND: {
			        print( "AND" );
			        break;
		        };;
		        case OR: {
			        print( "OR" );
			        break;
		        };;
		        case LSHIFT: {
			        print( "LSHIFT" );
			        break;
		        };;
		        case RSHIFT: {
			        print( "RSHIFT" );
			        break;
		        };;
		        case ARSHIFT: {
			        print( "ARSHIFT" );
			        break;
		        };;
		        case XOR: {
			        print( "XOR" );
			        break;
		        };;
		        case COUNT: {
			        print( "COUNT" );
			        break;
		        };;
		        case EQ: {
			        print( "EQ" );
			        break;
		        };;
		        case NE: {
			        print( "NE" );
			        break;
		        };;
		        case LT: {
			        print( "LT" );
			        break;
		        };;
		        case LE: {
			        print( "LE" );
			        break;
		        };;
		        case GE: {
			        print( "GE" );
			        break;
		        };;
		        case ULT: {
			        print( "ULT" );
			        break;
		        };;
		        case ULE: {
			        print( "ULE" );
			        break;
		        };;
		        case UGT: {
			        print( "UGT" );
			        break;
		        };;
		        case UGE: {
			        print( "UGE" );
			        break;
		        };;
	        }
        }

		std::string strCJUMP( const CJUMP& op) {
			switch(op) {
				case CJUMP::J_EQ: {
					return ("EQ");

				}
				case CJUMP::J_NE: {
					return ("NE");

				}
				case CJUMP::J_LT: {
					return ("LT");

				}
				case CJUMP::J_GE: {
					return ("GE");

				}
				case CJUMP::J_ULT: {
					return ("ULT");

				}
				case CJUMP::J_ULE: {
					return ("ULE");

				}
				case CJUMP::J_UGT: {
					return ("UGT");

				}
				case CJUMP::J_UGE: {
					return ("UGE");

				}
				case CJUMP::J_COUNT: {
					return ("COUNT");

				}
				case CJUMP::J_GT: {
					return ("GT");

				}
				case CJUMP::J_LE: {
					return ("LE");

				}
			}
		}

        std::string strBinop( const BINOP& op ) {
	        switch ( op ) {
		        case PLUS: {
			        return "PLUS" ;

		        };
		        case MINUS: {
			        return "MINUS" ;

		        };;
		        case MUL: {
			        return "MUL" ;

		        };;
		        case DIV: {
			        return "DIV" ;

		        };;
		        case AND: {
			        return "AND" ;

		        };;
		        case OR: {
			        return "OR" ;

		        };;
		        case LSHIFT: {
			        return "LSHIFT" ;

		        };;
		        case RSHIFT: {
			        return "RSHIFT" ;

		        };;
		        case ARSHIFT: {
			        return "ARSHIFT" ;

		        };;
		        case XOR: {
			        return "XOR" ;

		        };;
		        case COUNT: {
			        return "COUNT" ;

		        };;
		        case EQ: {
			        return "EQ" ;

		        };;
		        case NE: {
			        return "NE" ;

		        };;
		        case LT: {
			        return "LT" ;

		        };;
		        case LE: {
			        return "LE" ;

		        };;
		        case GE: {
			        return "GE" ;

		        };;
		        case ULT: {
			        return "ULT" ;

		        };;
		        case ULE: {
			        return "ULE" ;

		        };;
		        case UGT: {
			        return "UGT" ;

		        };;
		        case UGE: {
			        return "UGE" ;

		        };;
	        }
        }

        int treeDeep = 0;

        friend class TreeWalker;
    };

    class TreeWalker {
        CIRTreePrinter* printer;
    public:
        TreeWalker( CIRTreePrinter* printer ) : printer( printer ) {
	        printer->treeDeep++;
        }

        ~TreeWalker() {
	        printer->treeDeep--;
        }
    };

}
#endif //MINIJAVACOMPILER_CIRTREEPRINTER_HPP
