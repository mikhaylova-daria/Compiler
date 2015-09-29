//
// Created by nicolai on 29.09.15.
//

#ifndef MINIJAVACOMPILER_DECLARATION_H_H
#define MINIJAVACOMPILER_DECLARATION_H_H

enum VarType { Int,Bool,NoType };
enum operation { Add,Sub,Mul,Div,Mod,And,Or,Not,Equals,NotEquals,Less,Greater,LessEquals,GreaterEquals };
enum InterruptionType { Return, Break, NoIterruption };

struct MyValue {
    VarType type;
    union {
        bool bool_value;
        int int_value;
    };
};

struct Var {
    MyValue value;
    bool is_assigned;
    bool is_declared;

    Var (bool is_assigned = false, bool is_declared = false, VarType type = NoType) : is_assigned(is_assigned), is_declared(is_declared) { value.type = type; }
};

#endif //MINIJAVACOMPILER_DECLARATION_H_H
