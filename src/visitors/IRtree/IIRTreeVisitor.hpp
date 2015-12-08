//
// Created by Ава Катушка on 01.12.15.
//

#ifndef MINIJAVACOMPILER_IIRTREEVISITOR_HPP
#define MINIJAVACOMPILER_IIRTREEVISITOR_HPP


#include <zconf.h>

namespace IRTree {
	//class declarations to avoid cyclic import
    class MoveStatement;
    class ExpressionStatement;
    class JumpStatement;
    class CJumpStatement;
	class SEQStatement;
    class StatementList;
    class LabelStatement;

    class ConstExp;
    class PlatformConstExp;
    class NameExp;
    class TempExp;
    class BinopExp;
    class MemExp;
    class ExpList;
    class CallExp;
    class ESEQExp;



    class IIRTreeVisitor {
        //virtual void Visit( const ) = 0;
        virtual void Visit( const MoveStatement* moveStatement ) = 0;
        virtual void Visit( const ExpressionStatement* expressionStatement) = 0;
        virtual void Visit( const JumpStatement* jumpStatement) = 0;
        virtual void Visit( const CJumpStatement* cJumpStatement) = 0;
        virtual void Visit( const SEQStatement* seqStatement) = 0;
        virtual void Visit( const StatementList* statementList) = 0;
        virtual void Visit( const LabelStatement* labelStatement) = 0;

        virtual void Visit( const ConstExp* constExp) = 0;
        virtual void Visit( const PlatformConstExp* platformConstExp ) = 0;
        virtual void Visit( const NameExp* nameExp) = 0;
        virtual void Visit( const TempExp* tempExp) = 0;
        virtual void Visit( const BinopExp* binopExp) = 0;
        virtual void Visit( const MemExp* memExp) = 0;
        virtual void Visit( const ExpList* expList) = 0;
        virtual void Visit( const CallExp* callExp) = 0;
        virtual void Visit( const ESEQExp* eseqExp) = 0;
    };
}


#endif //MINIJAVACOMPILER_IIRTREEVISITOR_HPP
