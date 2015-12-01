//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_TABLE_H
#define MINIJAVACOMPILER_TABLE_H


#include "../../symbol/Symbol.h"
#include "../../tree/Type.h"
#include <vector>

namespace SymbolTable {

    const int NOT_FOUND = -1;

    class CTypeInfo {
    public:
        CTypeInfo(const CSymbol *typeName, TType VarType) : TypeName(typeName), VarType(VarType) { }

        CTypeInfo() : TypeName(nullptr) { }

        bool operator==(const CTypeInfo &info) const { return VarType == info.VarType && TypeName == info.TypeName; }

        bool operator!=(const CTypeInfo &info) const { return !(*this == info); }

        TType VarType;
        const CSymbol *TypeName;
    };

    class CVarInfo {
    public:
        CVarInfo(const CSymbol *varName, const CTypeInfo &typeInfo) : VarName(varName), TypeInfo(typeInfo) { }

        CVarInfo() : VarName(nullptr) { }

        const CSymbol *VarName;
        CTypeInfo TypeInfo;
    };

    class CMethodInfo {
    public:

        CMethodInfo(const CSymbol *Name, CTypeInfo returnType) : Name(Name), ReturnType(returnType) { }

        CMethodInfo() : Name(nullptr) { }

        const CSymbol *Name;
        CTypeInfo ReturnType;
        std::vector<CVarInfo> Arguments;
        std::vector<CVarInfo> Vars;

        int FindVarPosition(const CSymbol *varName) {
            for (size_t i = 0; i < Vars.size(); i++) {
                if (Vars[i].VarName == varName) {
                    return static_cast<int>(i);
                }
            }
            return NOT_FOUND;
        }

        CVarInfo FindVarInfo(const CSymbol *varName) {
            for (size_t i = 0; i < Vars.size(); i++) {
                if (Vars[i].VarName == varName) {
                    return Vars[i];
                }
            }
            return CVarInfo();
        }

    };

    class CClassInfo {
    public:
        CClassInfo(const CSymbol *name, const CSymbol *base) : Name(name), Base(base) { }

        CClassInfo() : Name(nullptr) { }

        const CSymbol *Name;
        const CSymbol *Base;
        std::vector<CVarInfo> Vars;
        std::vector<CMethodInfo> Methods;
    };

    class CTable {
    public:
        std::vector<CClassInfo> Classes;

        std::vector<CClassInfo>::const_iterator FindClass(const CSymbol *name) {
            for (auto it = Classes.begin(); it != Classes.end(); it++) {
                if (it->Name == name) {
                    return it;
                }
            }
            return Classes.end();
        }

        int FindClassSize(const CSymbol *name) {
            auto classInfo = FindClass(name);
            if (classInfo == Classes.end()) {
                return NOT_FOUND;
            }
            int size = static_cast<int>(classInfo->Vars.size());
            int baseClassSize = (classInfo->Base == nullptr ? 0 : FindClassSize(classInfo->Name));
            assert(baseClassSize != NOT_FOUND);
            return size + baseClassSize;
        }

        const CSymbol *FindMethodBase(const CSymbol *className, const CSymbol *methodName) {
            auto currClass = FindClass(className);
            if (currClass == Classes.end()) {
                return nullptr;
            }
            for (size_t i = 0; i < currClass->Methods.size(); i++) {
                if (currClass->Methods[i].Name == methodName) {
                    return className;
                }
            }
            return FindMethodBase(currClass->Base, methodName);
        }

        CMethodInfo FindMethodInfo(const CSymbol *className, const CSymbol *methodName) {
            auto currClass = FindClass(className);
            if (currClass == Classes.end()) {
                return CMethodInfo();
            }
            for (size_t i = 0; i < currClass->Methods.size(); i++) {
                if (currClass->Methods[i].Name == methodName) {
                    return currClass->Methods[i];
                }
            }
            return FindMethodInfo(currClass->Base, methodName);
        }

        int FindVarPosition(const CSymbol *className, const CSymbol *varName) {
            auto currClass = FindClass(className);
            if (currClass == Classes.end()) {
                return NOT_FOUND;
            }
            for (size_t i = 0; i < currClass->Vars.size(); i++) {
                if (currClass->Vars[i].VarName == varName) {
                    return static_cast<int>(i);
                }
            }
            return FindVarPosition(currClass->Base, varName) + static_cast<int>(currClass->Vars.size());
        }

        CVarInfo FindVarInfo(const CSymbol *className, const CSymbol *varName) {
            auto currClass = FindClass(className);
            if (currClass == Classes.end()) {
                return CVarInfo();
            }
            for (size_t i = 0; i < currClass->Vars.size(); i++) {
                if (currClass->Vars[i].VarName == varName) {
                    return currClass->Vars[i];
                }
            }
            return FindVarInfo(currClass->Base, varName);
        }
    };
}
#endif //MINIJAVACOMPILER_TABLE_H
