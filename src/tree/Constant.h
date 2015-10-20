//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_CONSTANT_H
#define MINIJAVACOMPILER_CONSTANT_H

#include <string>
#include "Location.h"
#include "Visitor.h"

enum TConstantType {
    CT_INT,
    CT_BOOL
};

class CConstant : public IToken {
public:
    CConstant(const Location location, const TConstantType type, const char* value) :
            IToken(location), Type(type), Value(value) { }

    void Accept(IVisitor* visitor) const { visitor->Visit(this); }
    const TConstantType Type;
    const std::string Value;
};

#endif //MINIJAVACOMPILER_CONSTANT_H
