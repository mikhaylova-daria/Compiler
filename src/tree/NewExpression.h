//
// Created by nicolai on 27.10.15.
//

#ifndef MINIJAVACOMPILER_NEWEXPRESSION_H
#define MINIJAVACOMPILER_NEWEXPRESSION_H

#include "Location.h"
#include "Indentifier.h"
#include "Expression.h"

class CNewExpression : public IExpression {
public:
    CNewExpression(Location location, CIdentifier* id) : IExpression(location), Id(id) {}
    virtual ~CNewExpression() { delete Id; }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CIdentifier* Id;
};

class CIntArrayNewExpression : public IExpression {
public:
    CIntArrayNewExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CIntArrayNewExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
};

#endif //MINIJAVACOMPILER_NEWEXPRESSION_H
