//
// Created by nicolai on 29.09.15.
//

#ifndef MINIJAVACOMPILER_MINIJAVA_TYPES_H
#define MINIJAVACOMPILER_MINIJAVA_TYPES_H

#include <vector>

struct Token {
    int line;
    int position;
    int type;
    const char* name;
    std::vector<Token> args;
};

#endif //MINIJAVACOMPILER_MINIJAVA_TYPES_H
