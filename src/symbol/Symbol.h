//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_SYMBOL_H
#define MINIJAVACOMPILER_SYMBOL_H

#include <string>

class CSymbol {
    std::string name;
public:
    CSymbol(const std::string& str) : name(str) {}
};

class CStorage {
public:
    const CSymbol Get(const std::string& s) {
        return CSymbol(s);
    }
};

#endif //MINIJAVACOMPILER_SYMBOL_H
