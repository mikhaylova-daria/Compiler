//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_INDENTIFIER_H
#define MINIJAVACOMPILER_INDENTIFIER_H

#include "Location.h"
#include "Visitor.h"

class CIdentifier : public IToken {
public:
    CIdentifier(Location location, const char* id) : IToken(location), Id(id) {}

    void Accept(IVisitor* visitor) { return visitor->Visit(this); }

    std::string Id;
};

#endif //MINIJAVACOMPILER_INDENTIFIER_H
