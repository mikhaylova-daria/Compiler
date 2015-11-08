//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_EXPRESSION_H
#define MINIJAVACOMPILER_EXPRESSION_H

#include "Location.h"
#include "Visitor.h"
#include "Type.h"

class IExpression : public IToken {
public:
    IExpression(Location location) : IToken(location) {}
    virtual ~IExpression() {}

    virtual void Accept(IVisitor* visitor) const = 0;
};

class CVariable : public IExpression {
    const std::string name = "CVariable";

public:
    CVariable(Location location, CIdentifier* identifier) : IExpression(location), Identifier(identifier) {}
    ~CVariable() {
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    CIdentifier* Identifier;
};

class CConstant : public IExpression {
    const std::string name = "CConstant";

public:
    CConstant(const Location location, CType* type, const char* value) :
            IExpression(location), Type(type), Value(value) { }
    virtual ~CConstant() {
        delete Type;
    }

    void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    virtual const std::string& GetName() const { return name; }
    CType* Type;
    const std::string Value;
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
    BE_SQ_BRACKETS,
    BE_COUNT
};

class CBinaryExpression : public IExpression {
    const std::string name = "CBinaryExpression";

public:
    CBinaryExpression(Location location, const IExpression* leftExpr,
                      const IExpression* rightExpr, TBinaryExpression type) :
            IExpression(location),
            LeftExpr(leftExpr),
            RightExpr(rightExpr),
            BinaryExpressionType(type) {}

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }
    virtual ~CBinaryExpression() {
        delete LeftExpr;
        delete RightExpr;
    }

    const IExpression* LeftExpr;
    const IExpression* RightExpr;
    TBinaryExpression BinaryExpressionType;
};

class CNotExpression : public IExpression {
    const std::string name = "CNotExpression";

public:
    CNotExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CNotExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
};

class CLengthExpression : public IExpression {
    const std::string name = "CLengthExpression";

public:
    CLengthExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CLengthExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
};

class CBracketExpression : public IExpression {
    const std::string name = "CBracketExpression";

public:
    CBracketExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CBracketExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
};


#endif //MINIJAVACOMPILER_EXPRESSION_H
