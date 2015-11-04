//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_TYPECHECKER_H
#define MINIJAVACOMPILER_TYPECHECKER_H

#include "../../tree/MinijavaTree.h"

class CTypeChecker : public IVisitor {
    TType lastType;
    void printError(const IToken* token, const std::string msg);
    bool isCorrectTypes = true;
public:
    virtual void Visit(const CConstant *constant);

    virtual void Visit(const CBasicType *basicType);

    virtual void Visit(const CClassType *classType);

    virtual void Visit(const CBinaryExpression *binaryExpression);

    virtual void Visit(const CNotExpression *notExpression);

    virtual void Visit(const CLengthExpression *lengthExpression);

    virtual void Visit(const CExpressionList *expressionList);

    virtual void Visit(const CIdentifier *identifier);

    virtual void Visit(const CInvocation *invocation);

    virtual void Visit(const CNewExpression *newExpression);

    virtual void Visit(const CIntArrayNewExpression *intArrayNewExpression);

    virtual void Visit(const CStatementList *statementList);

    virtual void Visit(const CBracketStatement *bracketStatement);

    virtual void Visit(const CIfStatement *ifStatement);

    virtual void Visit(const CWhileStatement *whileStatement);

    virtual void Visit(const CPrintStatement *printStatement);

    virtual void Visit(const CAssignmentStatement *assignmentStatement);

    virtual void Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement);

    virtual void Visit(const CVarDeclaration *varDeclaration);

    virtual void Visit(const CVarDeclarationList *varDeclarationList);

    virtual void Visit(const CBracketExpression *bracketExpression);

    virtual void Visit(const CMethodArgumentsList *methodArgumentsList);

    virtual void Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration);

    virtual void Visit(const CMethodBodyDeclaration *methodBodyDeclaration);

    virtual void Visit(const CMethodDeclaration *methodDeclaration);

    virtual void Visit(const CMethodDeclarationList *methodDeclarationList);

    virtual void Visit(const CClassDeclaration *classDeclaration);

    virtual void Visit(const CMainClass *mainClass);

    virtual void Visit(const CClassDeclarationList *classDeclarationList);

    virtual void Visit(const CGoal *goal);
};


#endif //MINIJAVACOMPILER_TYPECHECKER_H
