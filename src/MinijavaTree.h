//
// Created by nicolai on 13.10.15.
//

#ifndef MINIJAVACOMPILER_MINIJAVATREE_H
#define MINIJAVACOMPILER_MINIJAVATREE_H

#include <iostream>

struct Location  {
    int firstLine;
    int firstColumn;
    int lastLine;
    int lastColumn;
    Location() {}
    Location(int _firstLine, int _firstColumn, int _lastLine, int _lastColumn)
            : firstLine(_firstLine), firstColumn(_firstColumn), lastLine(_lastLine), lastColumn(_lastColumn) {}
    void update(int line, int column) {
        firstLine = lastLine;
        firstColumn = lastColumn;
        lastLine = line;
        lastColumn = column;
    }
    void print() {
        std::cout << firstLine << ' ' << firstColumn;
        std::cout << ' ' << lastLine << ' ' << lastColumn << std::endl;
    }
};

class Token {
public:
    Location location;
    Token(const Location &location) : location(location) {}
};

union ConstantValue {
    int intValue;
    bool boolValue;
};

enum ConstantType {
    T_INT,
    T_BOOL,
    T_COUNT
};

class Constant {
public:
    virtual ConstantValue getValue() const = 0;
    virtual ConstantType getType() const = 0;
};

class ConstantInt {
    int value;
public:
    ConstantInt(int value) : value(value) {}
    ConstantValue getValue() {
        ConstantValue cv;
        cv.intValue = value;
        return cv;
    }
    ConstantType getType() { return ConstantType::T_INT; }
};

#endif //MINIJAVACOMPILER_MINIJAVATREE_H
