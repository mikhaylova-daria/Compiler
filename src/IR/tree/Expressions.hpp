//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_EXPRESSIONS_HPP
#define MINIJAVACOMPILER_EXPRESSIONS_HPP

#include "../../frame/Temp.hpp"
#include <memory>
#include "../../visitors/accept_visitor_template.hpp"
#include "../../visitors/IRtree/IIRTreeVisitor.hpp"
//public CAcceptVisitor<,IIRTreeVisitor>

namespace IRTree {

	class IIRStatement;
    class IIRExpression;

    using ExpPtr = std::shared_ptr<IIRExpression>;
	using ExpListPtr = std::shared_ptr<ExpList>;
	using StatementPtr = std::shared_ptr<IIRStatement>;
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

	class IIRExpression: public IAcceptVisitor<IIRTreeVisitor> {
	protected:
	    std::string name;

	public:
	    const std::string& getName() const {
		    return name;
	    }
	};

	class ConstExp : public CAcceptVisitor<ConstExp,IIRTreeVisitor, IIRExpression>{
		int value;
	public:
	    ConstExp( int value ) : value( value ) { name = "ConstExp"; }

	    int getValue() const {
		    return value;
	    }
	};

	enum TPlatformConstType {
		PCT_POINTER_SIZE
	};

	class PlatformConstExp : public CAcceptVisitor<PlatformConstExp,IIRTreeVisitor, IIRExpression> {
	public:
		PlatformConstExp(TPlatformConstType platformConstType) : PlatformConstType(platformConstType) { name = "PlatformConstExp"; }
		TPlatformConstType GetConstType() const { return PlatformConstType; }
	private:
		TPlatformConstType PlatformConstType;
	};


	class NameExp : public CAcceptVisitor<NameExp,IIRTreeVisitor,IIRExpression> {
		LabelPtr label;

	public:
	    NameExp( const LabelPtr& label ) : label( label ) { name = "NameExp"; }


	    const LabelPtr& getLabel() const {
		    return label;
	    }
	};


	class TempExp :public CAcceptVisitor<TempExp,IIRTreeVisitor, IIRExpression> {
		CTempPtr cTemp;

	public:
	    TempExp( const CTempPtr& cTemp ) : cTemp( cTemp ) { name = "TempExp"; }


	    const CTempPtr& getCTemp() const {
		    return cTemp;
	    }
	};


	class BinopExp : public CAcceptVisitor<BinopExp,IIRTreeVisitor, IIRExpression> {
		BINOP binop;
		ExpPtr left;
		ExpPtr right;


	public:
	    BinopExp( const BINOP& binop, const ExpPtr& left, const ExpPtr& right ) : binop( binop ), left( left ),
	                                                                              right( right ) { name = "BinopExp"; }
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


	//Mem - получение значения по адресу
    class MemExp : public CAcceptVisitor<MemExp,IIRTreeVisitor, IIRExpression> {
		ExpPtr exp;

	public:
	    MemExp( const ExpPtr& exp ) : exp( exp ) { name = "MemExp"; }
	};


	class ExpList: public CAcceptVisitor<ExpList, IIRTreeVisitor, IIRExpression> {
		ExpPtr head;
		ExpPtr next;

	public:
	    ExpList( const ExpPtr& head, const ExpPtr& next ) : head( head ), next( next ) { name = "ExpList"; }

	    const ExpPtr& getHead() const {
		    return head;
	    }

	    const ExpPtr& getNext() const {
		    return next;
	    }
	};


	class CallExp: public CAcceptVisitor<CallExp,IIRTreeVisitor, IIRExpression> {
		ExpPtr func;
		ExpListPtr args;

	public:
	    CallExp( const ExpPtr& func, const ExpListPtr& args ) : func( func ), args( args ) { name = "CallExp"; }


	    const ExpPtr& getFunc() const {
		    return func;
	    }

	    const ExpListPtr& getArgs() const {
		    return args;
	    }
	};


	class ESEQExp: public CAcceptVisitor<ESEQExp,IIRTreeVisitor, IIRExpression> {
		StatementPtr statement;
		ExpPtr expression;


	public:
	    ESEQExp( const StatementPtr& statement, const ExpPtr& expression ) : statement( statement ),
	                                                                         expression( expression ) { name = "ESEQExp"; }

	    const StatementPtr& getStatement() const {
		    return statement;
	    }

	    const ExpPtr& getExpression() const {
		    return expression;
	    }
	};


}

#endif //MINIJAVACOMPILER_EXPRESSIONS_HPP
