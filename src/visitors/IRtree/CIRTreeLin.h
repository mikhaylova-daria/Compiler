//
// Created by nicolai on 05.04.16.
//

#ifndef MINIJAVACOMPILER_CIRTREELIN_H
#define MINIJAVACOMPILER_CIRTREELIN_H

#include <memory>
#include "IIRTreeVisitor.hpp"
//#include "../../tree/Statment.h"
#include "../../IR/tree/Expressions.hpp"
#include "../../IR/tree/Statements.hpp"

namespace IRTree {

    struct CMovedCallExp;

    class CIRTreeLin : public IIRTreeVisitor {
    public:
        std::shared_ptr<StatementList> Linearize( StatementPtr statement );

        virtual void Visit(const MoveStatement *moveStatement);

        virtual void Visit(const ExpressionStatement *expressionStatement);

        virtual void Visit(const JumpStatement *jumpStatement);

        virtual void Visit(const CJumpStatement *cJumpStatement);

        virtual void Visit(const SEQStatement *seqStatement);

        virtual void Visit(const StatementList *statementList);

        virtual void Visit(const LabelStatement *labelStatement);

        virtual void Visit(const ConstExp *constExp);

        virtual void Visit(const PlatformConstExp *platformConstExp);

        virtual void Visit(const NameExp *nameExp);

        virtual void Visit(const TempExp *tempExp);

        virtual void Visit(const BinopExp *binopExp);

        virtual void Visit(const MemExp *memExp);

        virtual void Visit(const ExpList *expList);

        virtual void Visit(const CallExp *callExp);

        virtual void Visit(const ESEQExp *eseqExp);

    private:
        bool isLastSEQ;
        std::shared_ptr<StatementList> currStmList;
    };
}
#endif //MINIJAVACOMPILER_CIRTREELINEARIZATOR_H
