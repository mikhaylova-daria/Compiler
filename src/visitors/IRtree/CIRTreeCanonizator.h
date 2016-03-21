//
// Created by nicolai on 21.03.16.
//

#ifndef MINIJAVACOMPILER_CIRTREECANONIZATOR_H
#define MINIJAVACOMPILER_CIRTREECANONIZATOR_H

#include "IIRTreeVisitor.hpp"

namespace IRTree {
    class CIRTreeCanonizator : public IIRTreeVisitor {

        virtual void Visit( const MoveStatement* moveStatement ) override;
        virtual void Visit( const ExpressionStatement* expressionStatement) override;
        virtual void Visit( const JumpStatement* jumpStatement) override;
        virtual void Visit( const CJumpStatement* cJumpStatement) override;
        virtual void Visit( const SEQStatement* seqStatement) override;
        virtual void Visit( const StatementList* statementList) override;
        virtual void Visit( const LabelStatement* labelStatement) override;

        virtual void Visit( const ConstExp* constExp) override;
        virtual void Visit( const PlatformConstExp* platformConstExp ) override;
        virtual void Visit( const NameExp* nameExp) override;
        virtual void Visit( const TempExp* tempExp) override;
        virtual void Visit( const BinopExp* binopExp) override;
        virtual void Visit( const MemExp* memExp) override;
        virtual void Visit( const ExpList* expList) override;
        virtual void Visit( const CallExp* callExp) override;
        virtual void Visit( const ESEQExp* eseqExp) override;

    };
}

#endif //MINIJAVACOMPILER_CIRTREECANONIZATOR_H
