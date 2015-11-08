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

    bool operator==(const CTypeInfo& info) const { return VarType == info.VarType && TypeName == info.TypeName; }
    bool operator!=(const CTypeInfo& info) const { return !(*this == info); }

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

    CMethodInfo(const CSymbol* Name, CTypeInfo returnType) : Name(Name), ReturnType(returnType) { }
    CMethodInfo() : Name(nullptr) {}

    const CSymbol* Name;
    CTypeInfo ReturnType;
    std::vector<CVarInfo> Arguments;
    std::vector<CVarInfo> Vars;
};

class CClassInfo {
public:
    CClassInfo(const CSymbol* name, const CSymbol* base) : Name(name), Base(base) { }
    CClassInfo() : Name(nullptr) {}

    const CSymbol* Name;
    const CSymbol* Base;
    std::vector<CVarInfo> Vars;
    std::vector<CMethodInfo> Methods;
};

class CTable {
public:
    std::vector<CClassInfo> Classes;
};

#endif //MINIJAVACOMPILER_TABLE_H
