//
// Created by nicolai on 21.03.16.
//

#ifndef MINIJAVACOMPILER_CIRTREECANONIZATOR_H
#define MINIJAVACOMPILER_CIRTREECANONIZATOR_H

#include <memory>
#include "IIRTreeVisitor.hpp"
//#include "../../tree/Statment.h"
#include "../../IR/tree/Expressions.hpp"
#include "../../IR/tree/Statements.hpp"

namespace IRTree {

    struct CMovedCallExp;

    class IIRTreeCanonizatorVisitor : public IIRTreeVisitor {
    public:
        virtual void Visit( const CMovedCallExp* ) = 0;
    };

    struct CMovedCallExp : public IIRExpression {
        CMovedCallExp(ExpPtr exp) : CallExp(exp) {}
        ExpPtr CallExp;
        virtual void Accept(IIRTreeVisitor* visitor) override {
            IIRTreeCanonizatorVisitor* canonizatorVisitor = dynamic_cast<IIRTreeCanonizatorVisitor*>(visitor);
            assert(canonizatorVisitor != nullptr);
            return canonizatorVisitor->Visit(this);
        }
    };


    class CIRTreeCanonizator : public IIRTreeCanonizatorVisitor {
    public:

        CIRTreeCanonizator( CStorage& storage ): storage(storage) {}
        StatementPtr GetRoot() { return currentNode;}

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

        virtual void Visit( const CMovedCallExp* movedCallExp) override;
    private:
        class IRTreeNodeHolder{
        public:
            IRTreeNodeHolder operator=(const ExpPtr& exp) {
                expPtr = exp;
                isExpression = true;
                return *this;
            }
            IRTreeNodeHolder operator=(const ExpListPtr& exp) {
                expListPtr = exp;
                isExpression = true;
                return *this;
            }
            IRTreeNodeHolder operator=(const StatementPtr& st) {
                statementPtr = st;
                isExpression = false;
                return *this;
            }
            operator StatementPtr() const {
                assert(statementPtr != nullptr && !isExpression);
                return statementPtr;
            }
            operator ExpPtr() const {
                assert(expPtr != nullptr && isExpression);
                return expPtr;
            }
            operator ExpListPtr() const {
                assert(expPtr != nullptr && isExpression);
                return expListPtr;
            }
        private:
            StatementPtr statementPtr;
            ExpPtr expPtr;
            ExpListPtr expListPtr;
            bool isExpression;
        };

        class StmExpList {
        public:
            StmExpList() {}
            StmExpList(StatementPtr statement, ExpListPtr expList ) : statement(statement), expList(expList) {}
            StatementPtr statement;
            ExpListPtr expList;
        };

        ExpListPtr makeExpList(ExpPtr exp) {
            return ExpListPtr(new ExpList(exp, nullptr));
        }

        ExpListPtr makeExpList(ExpPtr exp1, ExpPtr exp2) {
            return ExpListPtr(new ExpList(exp1, makeExpList(exp2)));
        }

        static bool isNop( const StatementPtr a )
        {
            ExpressionStatement* exp = dynamic_cast<ExpressionStatement*>( a.get() );
            return exp != 0 && dynamic_cast<ConstExp*>( exp->getExpression().get() ) != 0;
        }

        static bool commute( const StatementPtr a, const ExpPtr b )
        {
            return a == nullptr || isNop(a)
                   || dynamic_cast<NameExp*>( b.get() ) != 0
                   || dynamic_cast<ConstExp*>( b.get() ) != 0 ;
        }

        StmExpList reorder(ExpListPtr expList) {
            if( expList == nullptr) {
                return StmExpList();
            }
            StmExpList tailList = reorder(expList->getNext());
            ExpPtr head = expList->getHead();
            ESEQExp* eseq = dynamic_cast<ESEQExp*>(head.get());
            if( eseq == nullptr) {
                tailList.expList = ExpListPtr(new ExpList(head, tailList.expList));
                return tailList;
            }
            if( commute(tailList.statement, eseq->getExpression())) {
                tailList.statement = StatementPtr(new SEQStatement(tailList.statement, eseq->getStatement()));
                tailList.expList = ExpListPtr(new ExpList(eseq->getExpression(), tailList.expList));
                return tailList;
            }
            ExpPtr tempExp(new TempExp(CTempPtr(new Temp::CTemp(storage)), 0));
            StatementPtr move(new MoveStatement(tempExp, eseq->getExpression()));
            tailList.statement = StatementPtr(new SEQStatement(tailList.statement, move));
            tailList.expList = ExpListPtr(new ExpList(tempExp, tailList.expList));
            return tailList;
        }

        ExpPtr wrap(StatementPtr stm, ExpPtr exp) {
            if( stm == nullptr) {
                return exp;
            }
            return ExpPtr(new ESEQExp(stm, exp));
        }

        StatementPtr wrap(StatementPtr stm1, StatementPtr stm2) {
            if( stm1 == nullptr) {
                return stm2;
            }
            return StatementPtr(new SEQStatement(stm1, stm2));
        }

        IRTreeNodeHolder currentNode;
        CStorage& storage;
    };
}

#endif //MINIJAVACOMPILER_CIRTREECANONIZATOR_H
