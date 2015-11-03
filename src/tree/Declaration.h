//
// Created by nicolai on 27.10.15.
//

#ifndef MINIJAVACOMPILER_DECLARATION_H
#define MINIJAVACOMPILER_DECLARATION_H

#include "Location.h"
#include "Type.h"
#include "Expression.h"
#include "Statment.h"

class CVarDeclaration : public IToken {
    std::string name = "CVarDeclaration";
public:
    const std::string& GetName() const const {
        return name;
    }

public:
    CVarDeclaration(Location location, IType* type, CIdentifier* identifier) :
            IToken(location),
            Type(type),
            Identifier(identifier) {}
    virtual ~CVarDeclaration() {
        delete Type;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IType* Type;
    CIdentifier* Identifier;
};

class CVarDeclarationList : public IToken {
    std::string name = "CVarDeclarationList";
public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CVarDeclarationList(Location location, CVarDeclaration* varDeclaration, CVarDeclarationList* next) :
            IToken(location),
            VarDeclaration(varDeclaration),
            Next(next) {}
    virtual ~CVarDeclarationList() {
        delete VarDeclaration;
        delete Next;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CVarDeclaration* VarDeclaration;
    CVarDeclarationList* Next;
};

class CMethodArgumentsList : public IToken {
    std::string name = "CMethodArgumentsList";
public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMethodArgumentsList(Location location, CVarDeclaration* varDeclaration, CMethodArgumentsList* next) :
        IToken(location),
        VarDeclaration(varDeclaration),
        Next(next) {}
    virtual ~CMethodArgumentsList() {
        delete VarDeclaration;
        delete Next;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CVarDeclaration* VarDeclaration;
    CMethodArgumentsList* Next;
};

class CMethodHeaderDeclaration : public IToken {
    std::string name = "CMethodHeaderDeclaration";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMethodHeaderDeclaration(Location location, IType* returnType,
                             CIdentifier* methodName,CMethodArgumentsList* methodArgumentList) :
            IToken(location),
            ReturnType(returnType),
            MethodName(methodName),
            MethodArgumentList(methodArgumentList) {}
    virtual ~CMethodHeaderDeclaration() {
        delete MethodArgumentList;
        delete ReturnType;
        delete MethodName;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IType* ReturnType;
    CIdentifier* MethodName;
    CMethodArgumentsList* MethodArgumentList;
};

class CMethodBodyDeclaration : public IToken {
    std::string name = "CMethodBodyDeclaration";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMethodBodyDeclaration(Location location, CVarDeclarationList* varDeclarationList,
                           CStatementList* statementList, IExpression* returnExpression) :
            IToken(location),
            VarDeclarationList(varDeclarationList),
            StatementList(statementList),
            ReturnExpression(returnExpression) {}

    virtual ~CMethodBodyDeclaration() {
        delete VarDeclarationList;
        delete StatementList;
        delete ReturnExpression;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CVarDeclarationList* VarDeclarationList;
    CStatementList* StatementList;
    IExpression* ReturnExpression;
};

class CMethodDeclaration : public IToken {
    std::string name = "CMethodDeclaration";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMethodDeclaration(Location location, CMethodHeaderDeclaration* methodHeaderDeclaration,
                       CMethodBodyDeclaration* methodBodyDeclaration) :
            IToken(location),
            MethodHeaderDeclaration(methodHeaderDeclaration),
            MethodBodyDeclaration(methodBodyDeclaration) {}
    virtual ~CMethodDeclaration() {
        delete MethodHeaderDeclaration;
        delete MethodBodyDeclaration;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CMethodHeaderDeclaration* MethodHeaderDeclaration;
    CMethodBodyDeclaration* MethodBodyDeclaration;
};

class CMethodDeclarationList : public IToken {
    std::string name = "CMethodDeclarationList";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMethodDeclarationList(Location location, CMethodDeclaration* methodDeclaration,
                           CMethodDeclarationList* methodDeclarationList) :
            IToken(location),
            MethodDeclaration(methodDeclaration),
            MethodDeclarationList(methodDeclarationList) {}
    virtual ~CMethodDeclarationList() {
        delete MethodDeclaration;
        delete MethodDeclarationList;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CMethodDeclaration* MethodDeclaration;
    CMethodDeclarationList* MethodDeclarationList;
};

class CClassDeclaration : public IToken {
    std::string name = "CClassDeclaration";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CClassDeclaration(Location location, CIdentifier* className, CIdentifier* baseClassName,
                      CVarDeclarationList* varDeclarationList, CMethodDeclarationList* methodDeclarationList) :
            IToken(location),
            ClassName(className),
            BaseClassName(baseClassName),
            VarDeclarationList(varDeclarationList),
            MethodDeclarationList(methodDeclarationList) {}
    ~CClassDeclaration() {
        delete ClassName;
        delete BaseClassName;
        delete VarDeclarationList;
        delete MethodDeclarationList;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CIdentifier* ClassName;
    CIdentifier* BaseClassName;
    CVarDeclarationList* VarDeclarationList;
    CMethodDeclarationList* MethodDeclarationList;
};

class CMainClass : public IToken {
    std::string name = "CMainClass";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CMainClass(Location location, CIdentifier* className,
               CIdentifier* argumentName, IStatement* mainFunctionStatement) :
            IToken(location),
            ArgumentName(argumentName),
            ClassName(className),
            MainFunctionStatement(mainFunctionStatement) {}
    ~CMainClass() {
        delete ClassName;
        delete ArgumentName;
        delete MainFunctionStatement;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CIdentifier* ClassName;
    CIdentifier* ArgumentName;
    IStatement* MainFunctionStatement;
};

class CClassDeclarationList : public IToken {
    std::string name = "CClassDeclarationList";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CClassDeclarationList(Location location, CClassDeclaration* classDeclaration,
                          CClassDeclarationList* classDeclarationList) :
            IToken(location),
            ClassDeclaration(classDeclaration),
            ClassDeclarationList(classDeclarationList) {}
    ~CClassDeclarationList() {
        delete ClassDeclaration;
        delete ClassDeclarationList;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CClassDeclaration* ClassDeclaration;
    CClassDeclarationList* ClassDeclarationList;
};

class CGoal : public IToken {
    std::string name = "CGoal";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CGoal(Location location, CMainClass* mainClass, CClassDeclarationList* classDeclarationList) :
            IToken(location),
            MainClass(mainClass),
            ClassDeclarationList(classDeclarationList) {}
    ~CGoal() {
        delete MainClass;
        delete ClassDeclarationList;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CMainClass* MainClass;
    CClassDeclarationList* ClassDeclarationList;
};

#endif //MINIJAVACOMPILER_DECLARATION_H
