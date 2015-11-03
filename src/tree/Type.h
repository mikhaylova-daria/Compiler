//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_TYPE_H
#define MINIJAVACOMPILER_TYPE_H

#include <cassert>
#include "Location.h"
#include "Visitor.h"
#include "Indentifier.h"

/* IType is an interface all types should implement according to the rule
 Type ::="int" "[" "]"
|	"boolean"
|	"int"
|	Identifier  */

enum TType {
    T_UNDEFINED, //It's just to be here. Maybe somebody would need it
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

//All types in one
/*  Type ::="int" "[" "]"
|	"boolean"
|	"int" */

class CBasicType : public IType {
    std::string name = "CBasicType";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CBasicType(Location location, TType type) : IType(location, type) {
        assert(type == T_INT || type == T_INT_ARRAY || type == T_BOOL);
    }
    virtual ~CBasicType() {}
    virtual void Accept(IVisitor* visitor) const { visitor->Visit(this); }
};

//Class type
/* Type ::= Identifier */
class CClassType : public IType {
    std::string name = "CClassType";

public:
    const std::string& GetName() const  {
	    return name;
    }

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
