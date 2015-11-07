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
    CTypeInfo(const CSymbol &ClassName, const TType &VarType) : ClassName(ClassName), VarType(VarType) { }

    TType VarType;
    CSymbol ClassName;
};

class CVarInfo {
public:
    CVarInfo(const CSymbol &VarName, const CTypeInfo &TypeInfo) : VarName(VarName), TypeInfo(TypeInfo) { }

    CSymbol VarName;
    CTypeInfo TypeInfo;
};

class CMethodInfo {
public:
    CSymbol Name;

    CMethodInfo(const CSymbol &Name, const std::vector<CVarInfo> &Arguments, const std::vector<CVarInfo> &Vars) :
            Name(Name), Arguments(Arguments), Vars(Vars) { }

    std::vector<CVarInfo> Arguments;
    std::vector<CVarInfo> Vars;
};

class CClassInfo {
public:
    CClassInfo(const CSymbol &Name, const std::vector<CVarInfo> &Vars, const std::vector<CMethodInfo> &Methods) :
            Name(Name), Vars(Vars), Methods(Methods) { }

    CSymbol Name;
    std::vector<CVarInfo> Vars;
    std::vector<CMethodInfo> Methods;
};

class CTable {
public:
    std::vector<CClassInfo> Classes;
};

#endif //MINIJAVACOMPILER_TABLE_H
