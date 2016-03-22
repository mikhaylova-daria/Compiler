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

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr&, IRTree::ExpPtr&) const override{
	        throw std::runtime_error("Unsupported operation: expression to conditional statement");
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
        CConditionalStatementConverter( const ExpPtr& leftExp, const ExpPtr& rightExp, CJUMP op) :
                leftExp(leftExp), rightExp(rightExp), op(op) { }

        virtual const IRTree::ExpPtr ToExp() const override {
	        throw std::runtime_error("Unsupported operation: conditional to expression");
        }

        virtual const IRTree::StatementPtr ToStm() const override {
	        throw std::runtime_error("Unsupported operation: conditional to expression");
        }

        virtual const IRTree::CJUMP ToConditional( IRTree::ExpPtr& left, IRTree::ExpPtr& right) const override {
	        left = leftExp;
            right = rightExp;
            return op;
        }

        virtual const IRTree::ExpListPtr ToExpList() const override {
            throw std::runtime_error("Unsupported operation: condition to expression list");
        }
        const ExpPtr& leftExp;
        const ExpPtr& rightExp;
        CJUMP op;

    private:

    };

}

#endif //MINIJAVACOMPILER_TRANSLATE_HPP
