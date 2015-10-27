//
// Created by nicolai on 27.10.15.
//

#ifndef MINIJAVACOMPILER_DECLARATION_H
#define MINIJAVACOMPILER_DECLARATION_H

#include "Location.h"
#include "Type.h"

class CVarDeclaration : public IToken {
public:
    CVarDeclaration(Location location, IType* type, CIdentifier* identifier) :
            IToken(location),
            Type(type),
            Identifier(identifier) {}
    virtual ~CVarDeclaration() {
        delete Type;
        delete Identifier;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    IType* Type;
    CIdentifier* Identifier;
};

class CVarDeclarationList : public IToken {
    CVarDeclarationList(Location location, CVarDeclaration* varDeclaration, CVarDeclarationList* next) :
            IToken(location),
            VarDeclaration(varDeclaration),
            Next(next) {}
    virtual ~CVarDeclarationList() {
        delete VarDeclaration;
        delete Next;
    }

    virtual void Accept(IVisitor* visitor) const { return visitor->Visit(this); }

    CVarDeclaration* VarDeclaration;
    CVarDeclarationList* Next;
};

#endif //MINIJAVACOMPILER_DECLARATION_H
