//
// Created by nicolai on 27.10.15.
//

#include "Location.h"
#include "Expression.h"

#ifndef MINIJAVACOMPILER_STATMENT_H
#define MINIJAVACOMPILER_STATMENT_H

//It is the Interface all statements should implement
//According to rule:
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

    virtual void Accept(IVisitor* visit) const = 0;
};

class CBracketStatement : public IStatement {
    std::string name = "CBracketStatement";
public:
    const std::string& GetName() const {
	    return name;
    }

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

//( Statement )* by rule STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION
class CStatementList : public IStatement {
    std::string name = "CStatementList";

public:
    const std::string& GetName() const {
	    return name;
    }

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
    std::string name = "CIfStatement";

public:
    const std::string& GetName() const {
	    return name;
    }

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

//"while" "(" Expression ")" Statement
class CWhileStatement : public IStatement {
    std::string name = "CWhileStatement";
public:
    const std::string& GetName() const {
	    return name;
    }

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


//	"System.out.println" "(" Expression ")" ";"
class CPrintStatement : public IStatement {
    std::string name = "CWhileStatement";
public:
    const std::string& GetName() const {
	    return name;
    }
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

// Identifier "=" Expression ";
class CAssignmentStatement : public IStatement {
    std::string name = "CAssignmentStatement";

public:
    const std::string& GetName() const {
	    return name;
    }
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

//Identifier "[" Expression "]" "=" Expression ";"
// First Expression is Index
// Second Expression is Expression

class CIntArrayAssignmentStatement : public IStatement {
    std::string name = "CIntArrayAssignmentStatement";

public:
    const std::string& GetName() const {
	    return name;
    }
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