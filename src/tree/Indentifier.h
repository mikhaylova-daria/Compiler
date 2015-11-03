//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_INDENTIFIER_H
#define MINIJAVACOMPILER_INDENTIFIER_H

#include "Location.h"
#include "Visitor.h"
#include "Expression.h"

class CIdentifier : public IExpression {
    std::string name = "CIdentifier";

public:
    const std::string& GetName() const{
	    return name;
    }
public:
    CIdentifier(Location location, const char* id) : IExpression(location), Id(id) {}

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    std::string Id;
};

class CThisIdentifier : public CIdentifier {
    std::string name = "CThisIdentifier";

public:
    const std::string& GetName() const {
	    return name;
    }
public:
    CThisIdentifier(Location location) : CIdentifier(location, "this") {}

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }
};

#endif //MINIJAVACOMPILER_INDENTIFIER_H
