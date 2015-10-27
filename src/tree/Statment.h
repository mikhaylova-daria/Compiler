//
// Created by nicolai on 27.10.15.
//

#include "Location.h"
#include "Expression.h"

#ifndef MINIJAVACOMPILER_STATMENT_H
#define MINIJAVACOMPILER_STATMENT_H

//It is the Interface all statements should implement
//Accoding to rule:
/* TODO: Statement	::=	"{" ( Statement )* "}"
|	"if" "(" Expression ")" Statement "else" Statement
|	"while" "(" Expression ")" Statement
|	"System.out.println" "(" Expression ")" ";"
|	Identifier "=" Expression ";"
|	Identifier "[" Expression "]" "=" Expression ";" */

class IStatement : public IToken {
public:
    IStatement(Location location) : IToken(location) {}
    virtual ~IStatement() {}

    virtual void Accept(IStatement* visit) const = 0;
};

#endif //MINIJAVACOMPILER_STATMENT_H
//( Statement )* by rule STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION
class CStatementList : public IStatement {
public:
    CStatementList(Location location, IStatement* statement, CStatementList* next = nullptr) :
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

//"if" "(" Expression ")" Statement "else" Statement
//First Statement is TrueStatement
//Second Statement is FalseStatement
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

//"while" "(" Expression ")" Statement
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


//	"System.out.println" "(" Expression ")" ";"
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

// Identifier "=" Expression ";
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

//Identifier "[" Expression "]" "=" Expression ";"
// First Expression is Index
// Second Expression is Expression
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
