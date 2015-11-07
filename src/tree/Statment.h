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
    const std::string name = "CBracketStatement";

public:
    CBracketStatement(Location location, IStatement* statement) :
    IStatement(location),
    Statement(statement) {}
    virtual ~CBracketStatement() {
        delete Statement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    IStatement* Statement;
};

//( Statement )* by rule STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION
class CStatementList : public IStatement {
    const std::string name = "CStatementList";

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
    virtual const std::string& GetName() const { return name; }

    IStatement* Statement;
    CStatementList* Next;
};

//"if" "(" Expression ")" Statement "else" Statement
//First Statement is TrueStatement
//Second Statement is FalseStatement
class CIfStatement : public IStatement {
    const std::string name = "CIfStatement";

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
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
    IStatement* TrueStatement;
    IStatement* FalseStatement;
};

//"while" "(" Expression ")" Statement
class CWhileStatement : public IStatement {
    const std::string name = "CWhileStatement";

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
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
    IStatement* Statement;
};


//	"System.out.println" "(" Expression ")" ";"
class CPrintStatement : public IStatement {
    const std::string name = "CPrintStatement";

public:
    CPrintStatement(Location location, IExpression* expression) :
            IStatement(location),
            Expression(expression) {}
    virtual ~CPrintStatement() {
        delete Expression;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
};

// Identifier "=" Expression ";
class CAssignmentStatement : public IStatement {
    const std::string name = "CAssignmentStatement";

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
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
    CIdentifier* Identifier;
};

//Identifier "[" Expression "]" "=" Expression ";"
// First Expression is Index
// Second Expression is Expression

class CIntArrayAssignmentStatement : public IStatement {
    const std::string name = "CIntArrayAssignmentStatement";

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
    virtual const std::string& GetName() const { return name; }

    IExpression* Expression;
    IExpression* Index;
    CIdentifier* Identifier;
};

#endif //MINIJAVACOMPILER_STATMENT_H