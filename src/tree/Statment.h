//
// Created by nicolai on 27.10.15.
//

#include "Location.h"
#include "Expression.h"

#ifndef MINIJAVACOMPILER_STATMENT_H
#define MINIJAVACOMPILER_STATMENT_H

class IStatement : public IToken {
public:
    IStatement(Location location) : IToken(location) {}
    virtual ~IStatement() {}

    virtual void Accept(IVisitor* visit) const = 0;
};

class CBracketStatement : public IStatement {
public:
    CBracketStatement(Location location, IStatement* statement) :
    IStatement(location),
    Statement(statement) {}
    virtual ~CBracketStatement() {
        delete Statement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IStatement* Statement;
};

class CStatementList : public IStatement {
public:
    CStatementList(Location location, IStatement* statement, CStatementList* next = 0) :
            IStatement(location),
            Statement(statement),
            Next(next) {}
    virtual ~CStatementList() {
        delete Statement;
        delete Next;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IStatement* Statement;
    CStatementList* Next;
};

class CIfStatement : public IStatement {
public:
    CIfStatement(Location location, IExpression* expression, IStatement* trueStatement, IStatement* falseStatement) :
            IStatement(location),
            Expression(expression),
            TrueStatement(trueStatement),
            FalseStatement(falseStatement) {}
    virtual ~CIfStatement() {
        delete Expression;
        delete TrueStatement;
        delete FalseStatement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    IStatement* TrueStatement;
    IStatement* FalseStatement;
};

class CWhileStatement : public IStatement {
public:
    CWhileStatement(Location location, IExpression* expression, IStatement* statement) :
            IStatement(location),
            Expression(expression),
            Statement(statement) {}
    virtual ~CWhileStatement() {
        delete Expression;
        delete Statement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    IStatement* Statement;
};


class CPrintStatement : public IStatement {
public:
    CPrintStatement(Location location, IExpression* expression) :
            IStatement(location),
            Expression(expression) {}
    virtual ~CPrintStatement() {
        delete Expression;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
};

class CAssignmentStatement : public IStatement {
public:
    CAssignmentStatement(Location location, IExpression* expression, CIdentifier* identifier) :
            IStatement(location),
            Expression(expression),
            Identifier(identifier) {}
    virtual ~CAssignmentStatement() {
        delete Expression;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    CIdentifier* Identifier;
};

class CIntArrayAssignmentStatement : public IStatement {
public:
    CIntArrayAssignmentStatement(Location location, IExpression* expression,
                                  IExpression* index, CIdentifier* identifier) :
            IStatement(location),
            Expression(expression),
            Index(index),
            Identifier(identifier) {}
    virtual ~CIntArrayAssignmentStatement() {
        delete Expression;
        delete Index;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    IExpression* Index;
    CIdentifier* Identifier;
};

#endif //MINIJAVACOMPILER_STATMENT_H