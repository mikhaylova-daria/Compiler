//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_TYPE_H
#define MINIJAVACOMPILER_TYPE_H

#include <cassert>
#include "Location.h"
#include "Visitor.h"
#include "Indentifier.h"
#include "../symbol/Symbol.h"

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

class CType : public IToken {
    const std::string name = "CType";
public:
    CType(Location location, TType type, const CSymbol* symbol) : IToken(location), Type(type), Name(symbol) {}
    virtual ~CType() {}

    virtual void Accept(IVisitor* visit) { visit->Visit(this); }
    const std::string& GetName() const { return name; }

    TType Type;
    const CSymbol* Name;
};

#endif //MINIJAVACOMPILER_TYPE_H
