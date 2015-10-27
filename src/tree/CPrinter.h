//
// Created by daria on 27.10.15.
//

#ifndef MINIJAVACOMPILER_CPRINTER_H
#define MINIJAVACOMPILER_CPRINTER_H

#include "Visitor.h"

class CPrinter : public IVisitor {
public:
    virtual ~IVisitor() {}

    virtual void Visit(const CConstant* constant);
    virtual void Visit(const CBasicType* basicType);
    virtual void Visit(const CClassType* classType);
    virtual void Visit(const CBinaryExpression* binaryExpression);
    virtual void Visit(const CNotExpression* notExpression);
    virtual void Visit(const CLengthExpression* lengthExpression);
    virtual void Visit(const CExpressionList* expressionList);
    virtual void Visit(const CIdentifier* identifier);
    virtual void Visit(const CInvocation* invocation);
    virtual void Visit(const CNewExpression* newExpression);
    virtual void Visit(const CIntArrayNewExpression* intArrayNewExpression);
    virtual void Visit(const CStatementList* statementList);
    virtual void Visit(const CIfStatement* ifStatement);
    virtual void Visit(const CWhileStatement* whileStatement);
    virtual void Visit(const CPrintStatement* printStatement);
    virtual void Visit(const CAssignmentExpression* assignmentExpression);
    virtual void Visit(const CIntArrayAssignmentExpression* arrayAssignmentExpression);
    virtual void Visit(const CVarDeclaration* varDeclaration);
    virtual void Visit(const CVarDeclarationList* varDeclarationList);
};

#endif //MINIJAVACOMPILER_CPRINTER_H
