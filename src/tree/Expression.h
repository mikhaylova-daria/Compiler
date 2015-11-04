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
    std::string name = "CVariable";
public:
    const std::string& GetName() const {
        return name;
    }
    CVariable(Location location, CIdentifier* identifier) : IExpression(location), Identifier(identifier) {}
    ~CVariable() {
        delete Identifier;
    }
    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    CIdentifier* Identifier;
};

class CThisExpression : public CVariable {
    std::string name = "CThisIdentifier";

public:
    const std::string& GetName() const {
        return name;
    }
public:
    CThisExpression(Location location) : CVariable(location, new CIdentifier(location, "this")) {}

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
};

class CConstant : public IExpression {
    std::string name = "CConstant";
public:
    const std::string& GetName() const {
        return name;
    }

    CConstant(const Location location, const TType type, const char* value) :
            IExpression(location), Type(type), Value(value) { }
    virtual ~CConstant() {}

    void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    const TType Type;
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
    BE_SQ_BRACKETS
};

class CBinaryExpression : public IExpression {
    std::string name = "CBinaryExpression";

public:
    const std::string& GetName() const {
        return name;
    }
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
    std::string name = "CNotExpression";

public:
    const std::string& GetName() const{
        return name;
    }
public:
    CNotExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CNotExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};

class CLengthExpression : public IExpression {
    std::string name = "CLengthExpression";

public:
    const std::string& GetName() const{
	    return name;
    }
public:
    CLengthExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CLengthExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};

class CBracketExpression : public IExpression {
    std::string name = "CBracketExpression";

public:
    const std::string& GetName() const{
	    return name;
    }
    CBracketExpression(Location location, IExpression* expression) : IExpression(location), Expression(expression) {}
    virtual ~CBracketExpression() { delete Expression; }

    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    IExpression* Expression;
};


#endif //MINIJAVACOMPILER_EXPRESSION_H
