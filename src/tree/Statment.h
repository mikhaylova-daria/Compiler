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

    virtual void Accept(IStatement* visit) const = 0;
};

#endif //MINIJAVACOMPILER_STATMENT_H

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
    CWhileStatement(Location location, IExpression* expression, IStatement* statement) :
            IStatement(location),
            Expression(expression),
            Statement(statement) {}
    virtual ~CIfStatement() {
        delete Expression;
        delete Statement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    IStatement* Statement;
};


class CPrintStatement : public IStatement {
    CPrintStatement(Location location, IExpression* expression) :
            IStatement(location),
            Expression(expression) {}
    virtual ~CPrintStatement() {
        delete Expression;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
};

class CAssignmentExpression : public IStatement {
    CAssignmentExpression(Location location, IExpression* expression, CIdentifier* identifier) :
            IStatement(location),
            Expression(expression),
            Identifier(identifier) {}
    virtual ~CIfStatement() {
        delete Expression;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    CIdentifier* Identifier;
};

class CIntArrayAssignmentExpression : public IStatement {
    CIntArrayAssignmentExpression(Location location, IExpression* expression,
                                  IExpression* index, CIdentifier* identifier) :
            IStatement(location),
            Expression(expression),
            Index(index),
            Identifier(identifier) {}
    virtual ~CIfStatement() {
        delete Expression;
        delete Index;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IExpression* Expression;
    IExpression* Index;
    CIdentifier* Identifier;
};
