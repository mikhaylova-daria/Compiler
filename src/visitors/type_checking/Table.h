//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_TABLE_H
#define MINIJAVACOMPILER_TABLE_H


#include "../../symbol/Symbol.h"
#include "../../tree/Type.h"
#include <vector>

class CTypeInfo {
public:
    CTypeInfo(const CSymbol* typeName, TType VarType) : TypeName(typeName), VarType(VarType) { }
    CTypeInfo() : TypeName(nullptr) {}

    TType VarType;
    const CSymbol* TypeName;
};

class CVarInfo {
public:
    CVarInfo(const CSymbol* varName, const CTypeInfo& typeInfo) : VarName(varName), TypeInfo(typeInfo) { }
    CVarInfo() : VarName(nullptr) {}

    const CSymbol* VarName;
    CTypeInfo TypeInfo;
};

class CMethodInfo {
public:

    CMethodInfo(const CSymbol* Name, const std::vector<CVarInfo> &Arguments, const std::vector<CVarInfo> &Vars) :
            Name(Name), Arguments(Arguments), Vars(Vars) { }
    CMethodInfo() : Name(nullptr) {}

    const CSymbol* Name;
    std::vector<CVarInfo> Arguments;
    std::vector<CVarInfo> Vars;
};

class CClassInfo {
public:
    CClassInfo(const CSymbol *name, const std::vector<CVarInfo> &vars, const std::vector<CMethodInfo> &methods) :
            Name(name), Vars(vars), Methods(methods) { }
    CClassInfo() : Name(nullptr) {}

    const CSymbol* Name;
    std::vector<CVarInfo> Vars;
    std::vector<CMethodInfo> Methods;
};

class CTable {
public:
    std::vector<CClassInfo> Classes;
};

#endif //MINIJAVACOMPILER_TABLE_H
