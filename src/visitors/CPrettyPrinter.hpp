//
// Created by daria on 27.10.15.
//

#ifndef MINIJAVACOMPILER_CPRETTYPRINTER_H
#define MINIJAVACOMPILER_CPRETTYPRINTER_H

#include "../tree/MinijavaTree.h"
#include "../Utils/ConsolePrinter.hpp"

class CPrettyPrinter : public IVisitor {
public:
    virtual ~CPrettyPrinter() { }

    virtual void Visit( const CConstant* constant );

    virtual void Visit( const CType* basicType );

    virtual void Visit( const CVariable* variable );

    virtual void Visit( const CBinaryExpression* binaryExpression );

    virtual void Visit( const CNotExpression* notExpression );

    virtual void Visit( const CLengthExpression* lengthExpression );

    virtual void Visit( const CExpressionList* expressionList );

    virtual void Visit( const CIdentifier* identifier );

    virtual void Visit( const CInvocation* invocation );

    virtual void Visit( const CNewExpression* newExpression );

    virtual void Visit( const CIntArrayNewExpression* intArrayNewExpression );

    virtual void Visit( const CStatementList* statementList );

    virtual void Visit( const CIfStatement* ifStatement );

    virtual void Visit( const CWhileStatement* whileStatement );

    virtual void Visit( const CPrintStatement* printStatement );

    virtual void Visit( const CVarDeclaration* varDeclaration );

    virtual void Visit( const CVarDeclarationList* varDeclarationList );

    virtual void Visit( const CBracketStatement* bracketStatement );

    virtual void Visit( const CAssignmentStatement* assignmentStatement );

    virtual void Visit( const CIntArrayAssignmentStatement* intArrayAssignmentStatement );

    virtual void Visit( const CBracketExpression* bracketExpression );

    virtual void Visit( const CMethodArgumentsList* methodArgumentsList );

    virtual void Visit( const CMethodHeaderDeclaration* methodHeaderDeclaration );

    virtual void Visit( const CMethodBodyDeclaration* methodBodyDeclaration );

    virtual void Visit( const CMethodDeclaration* methodDeclaration );

    virtual void Visit( const CMethodDeclarationList* methodDeclarationList );

    virtual void Visit( const CClassDeclaration* classDeclaration );

    virtual void Visit( const CMainClass* mainClass );

    virtual void Visit( const CClassDeclarationList* classDeclarationList );

    virtual void Visit( const CGoal* goal );

private:
    void print( const std::string& what ) {
        printTabs();
        ConsolePrinter::print(what);
        ConsolePrinter::printNewLine();
    }

    void printTabs() {
        for (int i = 0; i < treeDeep; i++) {
            ConsolePrinter::printTab();
        }
    }

    void print(TType type) {
        printTabs();
        ConsolePrinter::print(type);
        ConsolePrinter::printNewLine();
    }

    void print(TBinaryExpression type) {
        printTabs();
        ConsolePrinter::print(type);
        ConsolePrinter::printNewLine();
    }

    int treeDeep = 0;
};


#endif //MINIJAVACOMPILER_CPRETTYPRINTER_H

