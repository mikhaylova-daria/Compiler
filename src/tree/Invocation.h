//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_INVOCATION_H
#define MINIJAVACOMPILER_INVOCATION_H

#include "Expression.h"
#include "Indentifier.h"


// Arguments of function call
class CExpressionList : public IToken {
public:
    CExpressionList(Location location, IExpression* expression, CExpressionList* expressionList) :
            IToken(location),
            Expression(expression),
            ExpressionList(expressionList) {}
    virtual ~CExpressionList() {
        delete Expression;
        delete ExpressionList;
    }

    void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
    const IExpression* Expression;
    const CExpressionList* ExpressionList;
};

//It's a dot. Rule  Expression "." Identifier "(" ( Expression ( "," Expression )* )?
class CInvocation : public IExpression {
public:
    CInvocation(Location location, IExpression* expression, CIdentifier* identifier, CExpressionList* expressionList) :
        IExpression(location),
        Expression(expression),
        Identifier(identifier),
        ExpressionList(expressionList) {}
    virtual ~CInvocation() {
        delete Expression;
        delete Identifier;
        delete Expression;
    }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
    CIdentifier* Identifier;
    CExpressionList* ExpressionList;
};

#endif //MINIJAVACOMPILER_INVOCATION_H
