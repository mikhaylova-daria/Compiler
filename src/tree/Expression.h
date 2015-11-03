//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_EXPRESSION_H
#define MINIJAVACOMPILER_EXPRESSION_H

#include "Location.h"
#include "Visitor.h"

class IExpression : public IToken {
public:
    IExpression(Location location) : IToken(location) {}
    virtual ~IExpression() {}

    virtual void Accept(IVisitor* visitor) const = 0;
};

//Types of binary expression
enum TBinaryExpression {
    BE_PLUS,
    BE_MINUS,
    BE_MULTIPLICATION,
    BE_LESS,
    BE_AND,
    BE_EQUAL,
    //squere brackets
    BE_SQ_BRACKETS
};

class CBinaryExpression : public IExpression {
public:
    CBinaryExpression(Location location, const IExpression* leftExpr,
                      const IExpression* rightExpr, TBinaryExpression type) :
            IExpression(location),
            LeftExpr(leftExpr),
            RightExpr(rightExpr),
            BinaryExpressionType(type) {}

    const IExpression* LeftExpr;
    const IExpression* RightExpr;
    TBinaryExpression BinaryExpressionType;
    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual ~CBinaryExpression() {
        delete LeftExpr;
        delete RightExpr;
    }
};

class CNotExpression : public IExpression {
public:
    CNotExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CNotExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};

class CLengthExpression : public IExpression {
public:
    CLengthExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CLengthExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};

class CBracketExpression : public IExpression {
    CBracketExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CBracketExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};


#endif //MINIJAVACOMPILER_EXPRESSION_H
