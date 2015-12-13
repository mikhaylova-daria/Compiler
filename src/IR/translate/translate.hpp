//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_TRANSLATE_HPP
#define MINIJAVACOMPILER_TRANSLATE_HPP

#include "../tree/IRTree.hpp"
#include <exception>

namespace Translate {

    class ISubtreeWrapper {
    public:
        virtual ~ISubtreeWrapper() { }
        virtual const IRTree::ExpPtr ToExp() const = 0; // как Expr
        virtual const IRTree::StatementPtr ToStm() const = 0; // как Stm
        virtual const IRTree::StatementPtr ToConditional(
		        const IRTree::LabelPtr t, const IRTree::LabelPtr f) const = 0; // как if/jump
        //virtual const IRTree::ExpListPtr ToExpList() const = 0;
    };

    class CExpConverter : public ISubtreeWrapper {

    public:
        CExpConverter( const IRTree::ExpPtr& expr ) : expr( expr ) { }

        const IRTree::ExpPtr& getExpr() const {
	        return expr;
        }

        virtual const IRTree::ExpPtr ToExp() const {
	        return expr;
        }

        virtual const IRTree::StatementPtr ToStm() const {
            return IRTree::StatementPtr(new IRTree::ExpressionStatement(expr));
        }

        virtual const IRTree::StatementPtr ToConditional( const IRTree::LabelPtr t, const IRTree::LabelPtr f ) const {
	        throw std::runtime_error("Unsupported operation: expression to conditional statement");
        }

    private:
        IRTree::ExpPtr expr;
    };

    class CStatementConverter : public ISubtreeWrapper {

    public:
        CStatementConverter( const IRTree::StatementPtr& statement ) : statement( statement ) { }

        const IRTree::StatementPtr& getStatement() const {
	        return statement;
        }

        virtual const IRTree::ExpPtr ToExp() const {
	        throw std::runtime_error("Unsupported operation: statement to expression");
        }

        virtual const IRTree::StatementPtr ToStm() const {
	       return statement;
        }

        virtual const IRTree::StatementPtr ToConditional( const IRTree::LabelPtr t, const IRTree::LabelPtr f ) const {
	        throw std::runtime_error("Unsupported operation: statement to conditional statement");
        }

    private:
        IRTree::StatementPtr statement;
    };


    class CConditionalStatementConverter : public ISubtreeWrapper {

    public:
        CConditionalStatementConverter( const IRTree::StatementPtr& statement ) : statement( statement ) { }

        const IRTree::StatementPtr& getStatement() const {
	        return statement;
        }

        virtual const IRTree::ExpPtr ToExp() const {
	        throw std::runtime_error("Unsupported operation: statement to expression");
        }

        virtual const IRTree::StatementPtr ToStm() const {
	        return statement;
        }

        virtual const IRTree::StatementPtr ToConditional( const IRTree::LabelPtr t, const IRTree::LabelPtr f ) const {
	        return statement;
        }

    private:
        IRTree::StatementPtr statement;
    };

}

#endif //MINIJAVACOMPILER_TRANSLATE_HPP
