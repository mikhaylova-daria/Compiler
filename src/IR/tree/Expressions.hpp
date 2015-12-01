//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_EXPRESSIONS_HPP
#define MINIJAVACOMPILER_EXPRESSIONS_HPP

#include "../../frame/Temp.hpp"
#include <memory>


namespace IRTree {

	class IStatement;

    using ExpPtr = std::shared_ptr<IExpression>;
	using ExpListPtr = std::shared_ptr<ExpList>;
	using StatementPtr = std::shared_ptr<IStatement>;
    using LabelPtr = std::shared_ptr<Temp::CLabel>;
    using CTempPtr = std::shared_ptr<Temp::CTemp>;

	enum BINOP {
		PLUS,
		MINUS,
		MUL,
		DIV,
		AND,
		OR,
		LSHIFT,
		RSHIFT,
		ARSHIFT,
		XOR,
		COUNT,

		EQ,
		NE,
		LT,
		LE,
		GE,
		ULT,
		ULE,
		UGT,
		UGE
	};

	class IExpression {

    };

	class ConstExp : public IExpression {
		int value;
	public:
	    ConstExp( int value ) : value( value ) { }

	    int getValue() const {
		    return value;
	    }
	};

	enum TPlatformConstType {
		PCT_POINTER_SIZE
	};

	class PlatformConstExp : public IExpression {
	public:
		PlatformConstExp(TPlatformConstType platformConstType) : PlatformConstType(platformConstType) {}
		TPlatformConstType GetConstType() const { return PlatformConstType; }
	private:
		TPlatformConstType PlatformConstType;
	};


	class NameExp : public IExpression {
		LabelPtr label;

	public:
	    NameExp( const LabelPtr& label ) : label( label ) { }


	    const LabelPtr& getLabel() const {
		    return label;
	    }
	};


	class TempExp : public IExpression {
		CTempPtr cTemp;

	public:
	    TempExp( const CTempPtr& cTemp ) : cTemp( cTemp ) { }


	    const CTempPtr& getCTemp() const {
		    return cTemp;
	    }
	};


	class BinopExp : public IExpression {
		BINOP binop;
		ExpPtr left;
		ExpPtr right;


	public:
	    BinopExp( const BINOP& binop, const ExpPtr& left, const ExpPtr& right ) : binop( binop ), left( left ),
	                                                                              right( right ) { }
	    const BINOP& getBinop() const {
		    return binop;
	    }

	    const ExpPtr& getLeft() const {
		    return left;
	    }

	    const ExpPtr& getRight() const {
		    return right;
	    }
	};


	class MemExp : public IExpression {
		ExpPtr exp;

	public:
	    MemExp( const ExpPtr& exp ) : exp( exp ) { }
	};


	class ExpList {
		ExpPtr head;
		ExpPtr next;


	public:
	    ExpList( const ExpPtr& head, const ExpPtr& next ) : head( head ), next( next ) { }

	    const ExpPtr& getHead() const {
		    return head;
	    }

	    const ExpPtr& getNext() const {
		    return next;
	    }
	};


	class CallExp {
		ExpPtr func;
		ExpListPtr args;

	public:
	    CallExp( const ExpPtr& func, const ExpListPtr& args ) : func( func ), args( args ) { }


	    const ExpPtr& getFunc() const {
		    return func;
	    }

	    const ExpListPtr& getArgs() const {
		    return args;
	    }
	};


	class ESEQExp {
		StatementPtr statement;
		ExpPtr expression;


	public:
	    ESEQExp( const StatementPtr& statement, const ExpPtr& expression ) : statement( statement ),
	                                                                         expression( expression ) { }

	    const StatementPtr& getStatement() const {
		    return statement;
	    }

	    const ExpPtr& getExpression() const {
		    return expression;
	    }
	};


}

#endif //MINIJAVACOMPILER_EXPRESSIONS_HPP
