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
    const std::string name = "CVarDeclaration";

public:
    CVarDeclaration(Location location, CType* type, CIdentifier* identifier) :
            IToken(location),
            Type(type),
            Identifier(identifier) {}
    virtual ~CVarDeclaration() {
        delete Type;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    CType* Type;
    CIdentifier* Identifier;
};

class CVarDeclarationList : public IToken {
    const std::string name = "CVarDeclarationList";

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
    virtual const std::string& GetName() const { return name; }

    CVarDeclaration* VarDeclaration;
    CVarDeclarationList* Next;
};

class CMethodArgumentsList : public IToken {
    const std::string name = "CMethodArgumentsList";
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
    virtual const std::string& GetName() const { return name; }

    CVarDeclaration* VarDeclaration;
    CMethodArgumentsList* Next;
};

class CMethodHeaderDeclaration : public IToken {
    const std::string name = "CMethodHeaderDeclaration";
public:
    CMethodHeaderDeclaration(Location location, CType* returnType,
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
    virtual const std::string& GetName() const { return name; }

    CType* ReturnType;
    CIdentifier* MethodName;
    CMethodArgumentsList* MethodArgumentList;
};

class CMethodBodyDeclaration : public IToken {
    const std::string name = "CMethodBodyDeclaration";

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
    virtual const std::string& GetName() const { return name; }

    CVarDeclarationList* VarDeclarationList;
    CStatementList* StatementList;
    IExpression* ReturnExpression;
};

class CMethodDeclaration : public IToken {
    const std::string name = "CMethodDeclaration";

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
    virtual const std::string& GetName() const { return name; }

    CMethodHeaderDeclaration* MethodHeaderDeclaration;
    CMethodBodyDeclaration* MethodBodyDeclaration;
};

class CMethodDeclarationList : public IToken {
    const std::string name = "CMethodDeclarationList";

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
    virtual const std::string& GetName() const { return name; }

    CMethodDeclaration* MethodDeclaration;
    CMethodDeclarationList* MethodDeclarationList;
};

class CClassDeclaration : public IToken {
    const std::string name = "CClassDeclaration";
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
    virtual const std::string& GetName() const { return name; }

    CIdentifier* ClassName;
    CIdentifier* BaseClassName;
    CVarDeclarationList* VarDeclarationList;
    CMethodDeclarationList* MethodDeclarationList;
};

class CMainClass : public IToken {
    const std::string name = "CMainClass";

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
    virtual const std::string& GetName() const { return name; }

    CIdentifier* ClassName;
    CIdentifier* ArgumentName;
    IStatement* MainFunctionStatement;
};

class CClassDeclarationList : public IToken {
    const std::string name = "CClassDeclarationList";
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
    virtual const std::string& GetName() const { return name; }

    CClassDeclaration* ClassDeclaration;
    CClassDeclarationList* ClassDeclarationList;
};

class CGoal : public IToken {
    const std::string name = "CGoal";

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
    virtual const std::string& GetName() const { return name; }

    CMainClass* MainClass;
    CClassDeclarationList* ClassDeclarationList;
};

#endif //MINIJAVACOMPILER_DECLARATION_H
