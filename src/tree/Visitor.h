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

class IVisitor {
public:
    virtual void Visit(const CConstant* constant) = 0;
    virtual void Visit(const CBasicType* basicType) = 0;
    virtual void Visit(const CClassType* classType) = 0;
    virtual void Visit(const CBinaryExpression* binaryExpression) = 0;
    virtual void Visit(const CNotExpression* notExpression) = 0;
    virtual void Visit(const CLengthExpression* lengthExpression) = 0;
    virtual void Visit(const CExpressionList* expressionList) = 0;
    virtual void Visit(const CIdentifier* identifier) = 0;
    virtual void Visit(const CInvocation* invocation) = 0;
};

#endif //MINIJAVACOMPILER_VISITOR_H
