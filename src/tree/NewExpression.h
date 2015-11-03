//
// Created by nicolai on 27.10.15.
//

#ifndef MINIJAVACOMPILER_NEWEXPRESSION_H
#define MINIJAVACOMPILER_NEWEXPRESSION_H

#include "Location.h"
#include "Indentifier.h"
#include "Expression.h"

//"new" Identifier "(" ")"
class CNewExpression : public IExpression {
    std::string name = "CNewExpression";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CNewExpression(Location location, CIdentifier* id) : IExpression(location), Id(id) {}
    virtual ~CNewExpression() { delete Id; }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CIdentifier* Id;
};

//"new" "int" "[" Expression "]"
class CIntArrayNewExpression : public IExpression {
    std::string name = "CIntArrayNewExpression";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CIntArrayNewExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CIntArrayNewExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
};

#endif //MINIJAVACOMPILER_NEWEXPRESSION_H
