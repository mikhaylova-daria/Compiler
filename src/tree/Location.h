//
// Created by nicolai on 20.10.15.
//

#ifndef MINIJAVACOMPILER_LOCATION_H
#define MINIJAVACOMPILER_LOCATION_H

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

//IToken only keeps location; it's it only point
class IToken {
public:
    Location location;
    IToken(const Location &location) : location(location) {}
    virtual ~IToken() = 0;
};

#endif //MINIJAVACOMPILER_LOCATION_H
