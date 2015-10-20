//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_VISITOR_H
#define MINIJAVACOMPILER_VISITOR_H

class CConstant;
class CBasicType;
class CClassType;
class CBinaryExpression;

class IVisitor {
public:
    virtual void Visit(const CConstant* constant) = 0;
    virtual void Visit(const CBasicType* basicType) = 0;
    virtual void Visit(const CClassType* basicType) = 0;
    virtual void Visit(const CBinaryExpression* basicType) = 0;
};

#endif //MINIJAVACOMPILER_VISITOR_H
