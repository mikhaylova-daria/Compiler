//
// Created by Ава Катушка on 01.12.15.
//

#ifndef MINIJAVACOMPILER_CIRTREEPRINTER_HPP
#define MINIJAVACOMPILER_CIRTREEPRINTER_HPP
#include "IIRTreeVisitor.hpp"
#include "../../Utils/ConsolePrinter.hpp"

namespace IRTree {

    class CIRTreePrinter : public IIRTreeVisitor {

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
	        ConsolePrinter::print(what);
	        ConsolePrinter::printNewLine();
        }

        void printTabs() {
	        for (int i = 0; i < treeDeep; i++) {
		        ConsolePrinter::printTab();
	        }
        }

	    int treeDeep = 0;
	    friend class TreeWalker;
    };

    class TreeWalker {
	    CIRTreePrinter* printer;
    public:
	    TreeWalker(CIRTreePrinter* printer): printer(printer) {
		    printer->treeDeep++;
	    }

	    ~TreeWalker() {
		    printer->treeDeep--;
	    }
    };

}
#endif //MINIJAVACOMPILER_CIRTREEPRINTER_HPP
