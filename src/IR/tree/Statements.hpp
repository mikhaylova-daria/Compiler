//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_STATEMENTS_HPP
#define MINIJAVACOMPILER_STATEMENTS_HPP

#include "Expressions.hpp"

namespace IRTree {

	class IStatement {

	};

	class MoveStatement : public IStatement {
		ExpPtr destination;
		ExpPtr source;


	public:
	    MoveStatement( const ExpPtr& destination, const ExpPtr& source ) : destination( destination ),
	                                                                       source( source ) { }

	    const ExpPtr& getDestination() const {
		    return destination;
	    }

	    const ExpPtr& getSource() const {
		    return source;
	    }
	};


	class ExpressionStatement : public IStatement {
		ExpPtr expression;

	public:
	    ExpressionStatement( const ExpPtr& expression ) : expression( expression ) { }


	    const ExpPtr& getExpression() const {
		    return expression;
	    }
	};

	enum CJUMP {
	    EQ,
	    NE,
	    LT,
	    GT,
	    LE,
	    GE,
	    ULT,
	    ULE,
	    UGT,
	    UGE,
		COUNT,
	};

    class JumpStatement: public IStatement {
    public:
        JumpStatement(std::vector<LabelPtr> labelList, const ExpPtr expPtr) :
                labelList(labelList), expPtr(expPtr) {}
        const std::vector<LabelPtr> GetLabelList() const { return labelList; }
        const ExpPtr&
    private:
        std::vector<LabelPtr> labelList;
        const ExpPtr expPtr;
    };

	class CJumpStatement : public IStatement {
		CJUMP op;
		ExpPtr left;
		ExpPtr right;
		LabelPtr ifTrue;
		LabelPtr ifFalse;


	public:
	    CJumpStatement( const CJUMP& op, const ExpPtr& left, const ExpPtr& right, const LabelPtr& ifTrue,
	                    const LabelPtr& ifFalse ) : op( op ), left( left ), right( right ), ifTrue( ifTrue ),
	                                                ifFalse( ifFalse ) { }

	    const CJUMP& getOp() const {
		    return op;
	    }

	    const ExpPtr& getLeft() const {
		    return left;
	    }

	    const ExpPtr& getRight() const {
		    return right;
	    }

	    const LabelPtr& getIfTrue() const {
		    return ifTrue;
	    }

	    const LabelPtr& getIfFalse() const {
		    return ifFalse;
	    }
	};

	class SEQStatement: public IStatement {
		StatementPtr left;
		StatementPtr right;


	public:
	    SEQStatement( const StatementPtr& left, const StatementPtr& right ) : left( left ), right( right ) { }


	    const StatementPtr& getLeft() const {
		    return left;
	    }

	    const StatementPtr& getRight() const {
		    return right;
	    }
	};

	class StatementList {
		StatementPtr head;
		StatementPtr next;
	public:
        StatementList( const StatementPtr& head, const StatementPtr& next ) : head( head ), next( next ) { }

		const StatementPtr& getHead() const {
			return head;
		}

		const StatementPtr& getNext() const {
			return next;
		}
	};


	class LabelStatement : public IStatement {
		LabelPtr label;

	public:
	    LabelStatement( const LabelPtr& label ) : label( label ) { }

	    const LabelPtr& getLabel() const {
		    return label;
	    }
	};

}

#endif //MINIJAVACOMPILER_STATEMENTS_HPP
