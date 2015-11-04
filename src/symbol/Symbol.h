//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_SYMBOL_H
#define MINIJAVACOMPILER_SYMBOL_H

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace Symbol {
    class CSymbol {
    public:
        const std::string &GetName() const {
            return name;
        }

    private:
        friend class CStorage;

        CSymbol(const std::string &name) : name(name) { }

        const std::string name;
    };

    class CStorage {
    public:
        const CSymbol *Get(const std::string &s) {
            auto it = symbolMap.find(s);
            if (it == symbolMap.end()) {
                CSymbol *newSymbol = new CSymbol(s);
                symbols.push_back(std::unique_ptr<CSymbol>(newSymbol));
                it = symbolMap.insert(std::make_pair(s, newSymbol)).first;
            }
            return it->second;
        }

    private:
        std::unordered_map<std::string, CSymbol *> symbolMap;
        std::vector<std::unique_ptr<CSymbol>> symbols;
    };
}
#endif //MINIJAVACOMPILER_SYMBOL_H
