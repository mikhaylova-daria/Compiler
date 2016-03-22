//
// Created by Ава Катушка on 08.11.15.
//

#ifndef MINIJAVACOMPILER_STATEMENTS_HPP
#define MINIJAVACOMPILER_STATEMENTS_HPP

#include "Expressions.hpp"
#include "../../visitors/accept_visitor_template.hpp"
#include "../../visitors/IRtree/IIRTreeVisitor.hpp"
//public CAcceptVisitor<,IIRTreeVisitor>

namespace IRTree {

    class IIRStatement: public IAcceptVisitor<IIRTreeVisitor> {
    protected:
        std::string name;

    public:
        const std::string& getName() const {
	        return name;
        }
    };

    class MoveStatement : public CAcceptVisitor<MoveStatement,IIRTreeVisitor, IIRStatement> {
        ExpPtr destination;
        ExpPtr source;


    public:
        MoveStatement( const ExpPtr& destination, const ExpPtr& source ) : destination( destination ),
                                                                           source( source ) { name = "MoveStatement"; }

        const ExpPtr& getDestination() const {
	        return destination;
        }

        const ExpPtr& getSource() const {
	        return source;
        }
    };


    class ExpressionStatement : public CAcceptVisitor<ExpressionStatement,IIRTreeVisitor, IIRStatement> {
        ExpPtr expression;

    public:
        ExpressionStatement( const ExpPtr& expression ) : expression( expression ) { name = "ExpressionStatement"; }


        const ExpPtr& getExpression() const {
	        return expression;
        }
    };

    enum CJUMP {
        J_EQ,
        J_NE,
        J_LT,
        J_GT,
        J_LE,
        J_GE,
        J_ULT,
        J_ULE,
        J_UGT,
        J_UGE,
        J_COUNT,
    };

    class JumpStatement :  public CAcceptVisitor<JumpStatement,IIRTreeVisitor, IIRStatement> {
    public:
        JumpStatement( std::vector < LabelPtr > labelList, const ExpPtr expPtr ) :
		        labelList( labelList ), expPtr( expPtr ) { name = "JumpStatement"; }

        const std::vector < LabelPtr > GetLabelList() const { return labelList; }

        const std::vector < LabelPtr >& getLabelList() const {
	        return labelList;
        }

        const ExpPtr& getExpPtr() const {
	        return expPtr;
        }

    private:
        std::vector < LabelPtr > labelList;
        const ExpPtr expPtr;
    };

    class CJumpStatement : public CAcceptVisitor<CJumpStatement,IIRTreeVisitor, IIRStatement> {
        CJUMP op;
        ExpPtr left;
        ExpPtr right;
        LabelPtr ifTrue;
        LabelPtr ifFalse;


    public:
        CJumpStatement( const CJUMP& op, const ExpPtr& left, const ExpPtr& right, const LabelPtr& ifTrue,
                        const LabelPtr& ifFalse ) : op( op ), left( left ), right( right ), ifTrue( ifTrue ),
                                                    ifFalse( ifFalse ) { name = "CJumpStatement"; }

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

    class SEQStatement :  public CAcceptVisitor<SEQStatement,IIRTreeVisitor, IIRStatement> {
        StatementPtr left;
        StatementPtr right;


    public:
        SEQStatement( const StatementPtr& left, const StatementPtr& right ) : left( left ), right( right ) {
            assert(left != nullptr && right != nullptr);
            name = "SEQStatement";
        }


        const StatementPtr& getLeft() const {
	        return left;
        }

        const StatementPtr& getRight() const {
	        return right;
        }
    };

    class StatementList: public CAcceptVisitor<StatementList,IIRTreeVisitor, IIRStatement> {
        StatementPtr head;
        StatementPtr next;
    public:
        StatementList( const StatementPtr& head, const StatementPtr& next ) : head( head ), next( next ) { name = "StatementList"; }

        const StatementPtr& getHead() const {
	        return head;
        }

        const StatementPtr& getNext() const {
	        return next;
        }
    };


    class LabelStatement : public CAcceptVisitor<LabelStatement, IIRTreeVisitor, IIRStatement> {
        LabelPtr label;

    public:
        LabelStatement( const LabelPtr& label ) : label( label ) { name = "LabelStatement"; }

        const LabelPtr& getLabel() const {
	        return label;
        }
    };

}

#endif //MINIJAVACOMPILER_STATEMENTS_HPP
