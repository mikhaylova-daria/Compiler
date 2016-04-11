//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_TRANSLATE_HPP
#define MINIJAVACOMPILER_TRANSLATE_HPP

#include "../tree/IRTree.hpp"
#include <exception>

using namespace IRTree;

namespace Translate {

    class ISubtreeWrapper {
    public:
        virtual ~ISubtreeWrapper() { }
        virtual const IRTree::ExpPtr ToExp() const = 0; // как Expr
        virtual const IRTree::ExpListPtr ToExpList() const = 0;
        virtual const IRTree::StatementPtr ToStm() const = 0; // как Stm
        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr& left, IRTree::ExpPtr& right) const = 0; //как if/jump
    };

    class CExpConverter : public ISubtreeWrapper {

    public:
        CExpConverter( const IRTree::ExpPtr& expr ) : expr( expr ) { }

        virtual const IRTree::ExpPtr ToExp() const override {
	        return expr;
        }

        virtual const IRTree::StatementPtr ToStm() const override {
            return IRTree::StatementPtr(new IRTree::ExpressionStatement(expr));
        }

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr& left, IRTree::ExpPtr& right) const override{
	        left = expr;
            right = ExpPtr(new ConstExp(0));
            return CJUMP::J_NE;
        }

        virtual const IRTree::ExpListPtr ToExpList() const override {
            throw std::runtime_error("Unsupported operation: expression to expression list");
        }

    private:
        IRTree::ExpPtr expr;
    };

    class CExpListConverter : public ISubtreeWrapper {

    public:
        CExpListConverter( const IRTree::ExpListPtr& expr ) : exprList( expr ) { }

        virtual const IRTree::ExpPtr ToExp() const override {
            throw std::runtime_error("Unsupported operation: expression list to expression");
        }

        virtual const IRTree::StatementPtr ToStm() const override {
            throw std::runtime_error("Unsupported operation: expression list to statement");
        }

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr&, IRTree::ExpPtr& ) const override {
            throw std::runtime_error("Unsupported operation: expression list to conditional statement");
        }

        virtual const IRTree::ExpListPtr ToExpList() const override {
            return exprList;
        }

    private:
        IRTree::ExpListPtr exprList;
    };

    class CStatementConverter : public ISubtreeWrapper {

    public:
        CStatementConverter( const IRTree::StatementPtr& statement ) : statement( statement ) { }

        virtual const IRTree::ExpPtr ToExp() const override {
	        throw std::runtime_error("Unsupported operation: statement to expression");
        }

        virtual const IRTree::StatementPtr ToStm() const override {
	       return statement;
        }

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr&, IRTree::ExpPtr& ) const override {
	        throw std::runtime_error("Unsupported operation: statement to conditional statement");
        }

        virtual const IRTree::ExpListPtr ToExpList() const override {
            throw std::runtime_error("Unsupported operation: statement to expression list");
        }

    private:
        IRTree::StatementPtr statement;
    };


    class CConditionalStatementConverter : public ISubtreeWrapper {

    public:
        CConditionalStatementConverter( BINOP op, const ExpPtr& leftExp, const ExpPtr& rightExp ) :
                leftExp(leftExp), rightExp(rightExp), op(op) {
            assert(leftExp != nullptr && rightExp != nullptr);
            jmp = convert(op);
        }

        virtual const IRTree::ExpPtr ToExp() const override {
            return ExpPtr(new BinopExp(op, leftExp, rightExp));
        }

        virtual const IRTree::StatementPtr ToStm() const override {
	        throw std::runtime_error("Unsupported operation: conditional to expression");
        }

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr& left, IRTree::ExpPtr& right) const override {
	        left = leftExp;
            right = rightExp;
            return jmp;
        }

        virtual const IRTree::ExpListPtr ToExpList() const override {
            throw std::runtime_error("Unsupported operation: condition to expression list");
        }
        ExpPtr leftExp;
        ExpPtr rightExp;
        BINOP op;
        CJUMP jmp;

    private:
        CJUMP convert(BINOP op) {
            switch(op) {
                case BINOP::EQ : return CJUMP::J_EQ;
                case BINOP::GE : return CJUMP::J_GE;
                case BINOP::LE : return CJUMP::J_LE;
                case BINOP::LT : return CJUMP::J_LT;
                case BINOP::NE : return CJUMP::J_NE;
                case BINOP::UGE : return CJUMP::J_UGE;
                case BINOP::UGT : return CJUMP::J_UGT;
                case BINOP::ULT : return CJUMP::J_ULT;
                case BINOP::ULE : return CJUMP::J_ULE;
                default: assert(false);
            }
        }
    };

}

#endif //MINIJAVACOMPILER_TRANSLATE_HPP
