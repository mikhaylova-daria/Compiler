//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_INDENTIFIER_H
#define MINIJAVACOMPILER_INDENTIFIER_H

#include "Location.h"
#include "Visitor.h"
#include "../symbol/Symbol.h"

using namespace Symbol;

class CIdentifier : public IToken {
    const std::string name = "CIdentifier";

public:
    CIdentifier(Location location, const CSymbol* symbol) : IToken(location), Symbol(symbol) {}

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
    virtual const std::string& GetName() const { return name; }

    const CSymbol* Symbol;
};
#endif //MINIJAVACOMPILER_INDENTIFIER_H
