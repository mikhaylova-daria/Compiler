//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_INDENTIFIER_H
#define MINIJAVACOMPILER_INDENTIFIER_H

#include "Location.h"
#include "Visitor.h"
//#include "Expression.h"

class CIdentifier : public IToken {
    std::string name = "CIdentifier";

public:
    const std::string& GetName() const{
	    return name;
    }
public:
    CIdentifier(Location location, const char* id) : IToken(location), Id(id) {}

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    std::string Id;
};
#endif //MINIJAVACOMPILER_INDENTIFIER_H
