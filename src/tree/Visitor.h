//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_VISITOR_H
#define MINIJAVACOMPILER_VISITOR_H

class CConstant;
class CBasicType;
class CClassType;
class CBinaryExpression;
class CNotExpression;
class CLengthExpression;
class CExpressionList;
class CIdentifier;
class CInvocation;
class CNewExpression;
class CIntArrayNewExpression;
class CStatementList;
class CIfStatement;
class CWhileStatement;
class CPrintStatement;
class CAssignmentStatement;
class CIntArrayAssignmentStatement;
class CVarDeclaration;
class CVarDeclarationList;
class CBracketExpression;

class IVisitor {
public:
    virtual ~IVisitor() = 0 {}

    virtual void Visit(const CConstant* constant) = 0;
    virtual void Visit(const CBasicType* basicType) = 0;
    virtual void Visit(const CClassType* classType) = 0;
    virtual void Visit(const CBinaryExpression* binaryExpression) = 0;
    virtual void Visit(const CNotExpression* notExpression) = 0;
    virtual void Visit(const CLengthExpression* lengthExpression) = 0;
    virtual void Visit(const CExpressionList* expressionList) = 0;
    virtual void Visit(const CIdentifier* identifier) = 0;
    virtual void Visit(const CInvocation* invocation) = 0;
    virtual void Visit(const CNewExpression* newExpression) = 0;
    virtual void Visit(const CIntArrayNewExpression* intArrayNewExpression) = 0;
    virtual void Visit(const CStatementList* statementList) = 0;
    virtual void Visit(const CIfStatement* ifStatement) = 0;
    virtual void Visit(const CWhileStatement* whileStatement) = 0;
    virtual void Visit(const CPrintStatement* printStatement) = 0;
    virtual void Visit(const CAssignmentStatement* assignmentStatement) = 0;
    virtual void Visit(const CIntArrayAssignmentStatement* intArrayAssignmentStatement) = 0;
    virtual void Visit(const CVarDeclaration* varDeclaration) = 0;
    virtual void Visit(const CVarDeclarationList* varDeclarationList) = 0;
    virtual void Visit(const CBracketExpression* bracketExpression) = 0;
};

#endif //MINIJAVACOMPILER_VISITOR_H
