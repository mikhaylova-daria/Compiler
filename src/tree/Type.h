//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_TYPE_H
#define MINIJAVACOMPILER_TYPE_H

#include <cassert>
#include "Location.h"
#include "Visitor.h"
#include "Indentifier.h"

enum TType {
    T_UNDEFINED,
    T_INT,
    T_INT_ARRAY,
    T_BOOL,
    T_CLASS
};

class IType : public IToken {
public:
    IType(Location location, TType type) : IToken(location), Type(type) {}
    virtual ~IType() {}

    TType Type;
    virtual void Accept(IVisitor* visit) const = 0;
};

class CBasicType : public IType {
public:
    CBasicType(Location location, TType type) : IType(location, type) {
        assert(type == T_INT || type == T_INT_ARRAY || type == T_BOOL);
    }
    virtual ~CBasicType() {}
    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
};

class CClassType : public IType {
public:
    CClassType(Location location, CIdentifier* className) :
            IType(location, T_CLASS),
            ClassName(className) {}
    virtual ~CClassType() {
        delete ClassName;
    }
    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }

    CIdentifier* ClassName;
};

#endif //MINIJAVACOMPILER_TYPE_H
