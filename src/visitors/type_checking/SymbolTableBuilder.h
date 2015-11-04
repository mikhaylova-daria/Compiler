//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_SYMBOLTABLEBUILDER_H
#define MINIJAVACOMPILER_SYMBOLTABLEBUILDER_H


#include "../../tree/MinijavaTree.h"
#include "Table.h"

class CSymbolTableBuilder : public IVisitor {
    CClassInfo currentCLass;
    CMethodInfo currentMethod;
    CTable table;
    CTypeInfo lastType;
    CStorage storage;
public:
    virtual ~CSymbolTableBuilder();

    virtual void Visit(const CConstant *constant) override;

    virtual void Visit(const CBinaryExpression *binaryExpression) override;

    virtual void Visit(const CNotExpression *notExpression) override;

    virtual void Visit(const CLengthExpression *lengthExpression) override;

    virtual void Visit(const CExpressionList *expressionList) override;

    virtual void Visit(const CIdentifier *identifier) override;

    virtual void Visit(const CInvocation *invocation) override;

    virtual void Visit(const CNewExpression *newExpression) override;

    virtual void Visit(const CIntArrayNewExpression *intArrayNewExpression) override;

    virtual void Visit(const CStatementList *statementList) override;

    virtual void Visit(const CBracketStatement *bracketStatement) override;

    virtual void Visit(const CIfStatement *ifStatement) override;

    virtual void Visit(const CWhileStatement *whileStatement) override;

    virtual void Visit(const CPrintStatement *printStatement) override;

    virtual void Visit(const CAssignmentStatement *assignmentStatement) override;

    virtual void Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) override;

    virtual void Visit(const CVarDeclaration *varDeclaration) override;

    virtual void Visit(const CVarDeclarationList *varDeclarationList) override;

    virtual void Visit(const CBracketExpression *bracketExpression) override;

    virtual void Visit(const CMethodArgumentsList *methodArgumentsList) override;

    virtual void Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) override;

    virtual void Visit(const CMethodBodyDeclaration *methodBodyDeclaration) override;

    virtual void Visit(const CMethodDeclaration *methodDeclaration) override;

    virtual void Visit(const CMethodDeclarationList *methodDeclarationList) override;

    virtual void Visit(const CClassDeclaration *classDeclaration) override;

    virtual void Visit(const CMainClass *mainClass) override;

    virtual void Visit(const CClassDeclarationList *classDeclarationList) override;

    virtual void Visit(const CGoal *goal) override;
};


#endif //MINIJAVACOMPILER_SYMBOLTABLEBUILDER_H
