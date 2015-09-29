//
// Created by nicolai on 29.09.15.
//

#ifndef MINIJAVACOMPILER_JAVAHELP_H
#define MINIJAVACOMPILER_JAVAHELP_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

#include "Declaration.h"

class Method;
class ArgumentList;
class Node;
class MyExpr;
class StatementList;
class ParamList;

const char* toString(VarType type);
const char* toString(MyValue value);

extern vector<string> mainArgs;
extern string mainArgsId;

class Node {
private:
    map<string, Var> vars;
    vector<Node*> nodes;
public:
    Node* root;
    Node(Node* root = NULL): root(root) {}

    bool isDeclared(const string & name) {
        auto it = vars.find(name);
        return ( it != vars.end() ) ? true : (root == NULL) ? false : root->isDeclared(name);
    }

    void addSubNode(Node* subNode){
        nodes.push_back(subNode);
    }
    void clearVars() {
        vars.clear();
    }

    Var getVar(const string & name) {
        auto it = vars.find(name);
        if (it == vars.end() && root == NULL) {
            cout << "Error: undeclared var" << name << endl;
            exit(1);
        }
        return (it == vars.end()) ? root->getVar(name) : it->second;
    }
    void declareVar(const string & name, VarType type) {
        if (isDeclared(name)) {
            cout << "Error: redefinition of" << name << endl;
            exit(1);
        }
        vars.insert({name, Var(false, true, type)});
    }
    void setVar(const string & name, MyValue value) {
        auto it = vars.find(name);
        if (it == vars.end()) {
            if (root != NULL) {
                root->setVar(name, value);
            }
            else {
                cout << "Error: assignment to undeclared var:" << name << endl;
                exit(1);
            }
            return;
        }
        Var& v = it->second;
        if (v.value.type != value.type) {
            cout << "Error: conversion error: can't convert "
            << toString(value.type) << " to " << toString(v.value.type) << endl;
            exit(1);
        }
        v.is_assigned = true;
        v.value = value;
    }
};

class MyExpr {
public:
    virtual MyValue exec(Node* node) = 0;
};

class Statement {
public:
    virtual InterruptionType execute(Node* node) = 0;
};

class Argument {
private:
    string Id;
    VarType type;

public:
    Argument(const string & name, VarType type)
    {
        this->Id = name;
        this->type = type;
    }
    Argument(){}

    friend class Method;
};

class ArgumentList {
private:
    vector<Argument*> args;
public:
    int size()
    {
        return args.size();
    }

    Argument* getAt(int index)
    {
        return args[index];
    }

    void add(Argument* arg)
    {
        args.push_back(arg);
    }
};

class Method {
protected:
    Node* methodNode;
    VarType returnType;
    ArgumentList* arguments;
    Statement* body;
    MyValue returnValue;
    int argumentsPassed;

public:
    string Id;

    Method(const char* name, VarType returnType, ArgumentList* args) : Id (name), returnType (returnType), arguments (args),                                argumentsPassed (0) {};

    void setBody(Statement* body) { this->body = body; }

    void setNode(Node* methodNode) { this->methodNode = methodNode; }

    void setReturnValue(MyValue value) { returnValue = value; }

    VarType getReturnType() { return returnType; }

    const char* getId() { return Id.c_str(); }

    virtual void addArg(MyValue value) {
        if (argumentsPassed + 1 > arguments->size()) {
            cout << "Error: " << Id << ": too many arguments" << endl;
            exit(1);
        }
        Argument* arg = arguments->getAt(argumentsPassed);
        if (value.type != arg->type) {
            fprintf(stderr, "Error: '%s': cannot convert parameter %d from %s to %s",
                    Id.c_str(), argumentsPassed + 1, toString(value.type), toString(arg->type));
            exit(1);
        }
        methodNode->declareVar(arg->Id, value.type);
        methodNode->setVar(arg->Id, value);
        argumentsPassed += 1;
    }

    virtual MyValue run() {
        if (argumentsPassed != arguments->size()) {
            cout << "Error: " << Id << ": too few arguments" << endl;
            exit(1);
        }
        argumentsPassed = 0;
        InterruptionType result = body->execute(methodNode);
        if (result == Return) {
            return returnValue;
        } else  {
            if (returnType == NoType) {
                return MyValue();
            }
            else {
                cout << "Error: "<< Id << ": missreturn statement" << endl;
                exit(1);
            }
        }
    }

};

class StatementList : public Statement {
private:
    vector<Statement*> statements;
public:
    StatementList() {}

    void add(Statement* stmt)
    {
        statements.push_back(stmt);
    }

    InterruptionType execute(Node* node)
    {
        InterruptionType result;
        for(auto it = statements.begin(); it != statements.end(); ++it)
        {
            result = (*it)->execute(node);
            if (result != NoIterruption)
            {
                return result;
            }
        }
        return NoIterruption;
    }
};


class MainClass {
public:
    Node* classNode;
    StatementList* FieldsDeclaration;
    Method* main;
    map<string, Method*> methods;
    string Id;

    MainClass() : main(NULL), classNode(new Node()), FieldsDeclaration(new StatementList()) {};

    void setName(const char* name) {   Id = name; }

    Node* getNode() {
        return classNode;
    }

    void setMain(Method* main) {
        this->main = main;
    }

    Method* getMethod(const string & Id) {
        auto it = methods.find(Id);
        return (it == methods.end()) ? NULL : it->second;
    }

    void addFieldDeclaration(Statement* stmt) { FieldsDeclaration->add(stmt); }

    void run() {
        if (!main) {
            cout << "Error: main method not found" << endl;
            exit(1);
        }

        FieldsDeclaration->execute(classNode);
        main->run();
    }
    void addMethod(Method* method) {
        if (methods.find(method->Id) != methods.end()) {
            cout << "Error method redeclaration: " << method->Id;
            exit(1);
        }
        method->setNode(classNode);
        methods.insert(make_pair(method->Id, method));
    }
};

class LibraryMethod : public Method {
protected:
    vector<MyValue> args;
public:
    LibraryMethod(const char* name, VarType returnType, ArgumentList* args): Method(name, returnType, args) {}
    void setNode();
    virtual MyValue run() = 0;
    void addArg(MyValue value) { args.push_back(value); }
};

class PrintlnMethod : public LibraryMethod {
public:
    PrintlnMethod(): LibraryMethod("println", NoType, NULL) {}
    virtual MyValue run() {
        for (auto arg: args) {
            cout << toString(arg) << " ";
        }
        if (args.size() > 0) {
            cout << endl;
        }
        args.clear();
        return MyValue();
    }
};

int parseInt(const string & st);

class GetIntArgMethod : public LibraryMethod {
public:
    GetIntArgMethod(): LibraryMethod("getIntArgument", Int, NULL) {}
    virtual MyValue run() {
        if (args.size() < 2) {
            fprintf(stderr, "'%s': too few arguments", getId());
            exit(1);
        }
        if (args.size() > 2) {
            fprintf(stderr, "'%s': too many arguments", getId());
            exit(1);
        }
        if (args[0].type != Int) {
            fprintf(stderr, "'%s': cannot convert parameter 1 from %s to String[]",
                    getId(), toString(args[0].type));
            exit(1);
        }
        if (args[0].int_value != -1) {
            fprintf(stderr, "'%s': incorrect parameter 1", getId());
            exit(1);
        }
        int index = args[1].int_value;
        if (index >= mainArgs.size())
        {
            fprintf(stderr, "'%s': index out of range", getId());
            exit(1);
        }
        int value = parseInt(mainArgs[index]);
        MyValue result;
        result.type = Int;
        result.int_value = value;
        args.clear();
        return result;
    }
};

bool parseBool(const string & st);

class GetBoolArgMethod : public LibraryMethod {
public:
    GetBoolArgMethod(): LibraryMethod("getBooleanArgument", Int, NULL) {}
    virtual MyValue run() {
        if (args.size() < 2)
        {
            fprintf(stderr, "'%s': too few arguments", getId());
            exit(1);
        }

        if (args.size() > 2)
        {
            fprintf(stderr, "'%s': too many arguments", getId());
            exit(1);
        }

        if (args[0].type != Int)
        {
            fprintf(stderr, "'%s': cannot convert parameter 1 from %s to String[]", getId(), toString(args[0].type));
            exit(1);
        }

        if (args[0].int_value != -1)
        {
            fprintf(stderr, "'%s': incorrect parameter 1", getId());
            exit(1);
        }

        int index = args[1].int_value;

        if (index >= mainArgs.size())
        {
            fprintf(stderr, "'%s': index out of range", getId());
            exit(1);
        }

        bool value = parseBool(mainArgs[index]);
        MyValue result;
        result.type = Bool;
        result.bool_value = value;
        args.clear();
        return result;
    }
};

ArgumentList*  makeList(int count, ...);


class AssertTrueMethod : public LibraryMethod {
public:
    AssertTrueMethod(): LibraryMethod("assertTrue", NoType, makeList(Bool))  {}
    virtual MyValue run() {
        if (args.size() < 1) {
            fprintf(stderr, "'%s': too few arguments", getId());
            exit(1);
        }

        if (args[0].type != Bool) {
            fprintf(stderr,"'%s': cannot convert to bool", toString(args[0].type));
            exit(1);
        }

        if (args[0].bool_value != true) {
            fprintf(stderr, "assertion error");
            exit(1);
        }
        args.clear();
        return MyValue();
    }
};

class NodeStatement : public Statement {
private:
    StatementList* body;
public:
    NodeStatement(StatementList* body): body (body) {}
    InterruptionType execute(Node* node) {
        return body->execute(new Node(node));
    }
};

class Library: public MainClass {
public:
    Library() {
        Id = "StaticJavaLib";
        Method* println = new PrintlnMethod();
        addMethod(println);

        Method* assertTrue = new AssertTrueMethod();
        addMethod(assertTrue);

        Method* getInt = new GetIntArgMethod();
        addMethod(getInt);

        Method* getBool = new GetBoolArgMethod();
        addMethod(getBool);
    }
    Node* getNode();
    void run();
};


class Declaration : public Statement {
private:
    string Id;
    VarType type;
    MyExpr* value;
public:
    Declaration(const char* name, VarType type, MyExpr* value = NULL)
    {
        this->Id = name;
        this->type = type;
        this->value = value;
    }

    InterruptionType execute(Node* node)
    {
        node->declareVar(Id, type);
        if (value != NULL)
        {
            node->setVar(Id, value->exec(node));
        }
        return NoIterruption;
    }
};

class Assignment : public Statement {
private:
    string Id;
    MyExpr* value;
public:
    Assignment(const char * name, MyExpr* value)
    {
        this->Id = name;
        this->value = value;
    }

    InterruptionType execute(Node* node)
    {
        node->setVar(Id, value->exec(node));
        return NoIterruption;
    }
};

class ReturnStatement : public Statement
{
private:
    MyExpr* value;
    Method* method;
public:
    ReturnStatement(MyExpr* value, Method* method): value(value), method(method) {}

    InterruptionType execute(Node* node) {
        if (value == NULL) {
            if (method->getReturnType() != NoType) {
                cout << "Error:" << method->Id << ": function must return a value" << endl;
                exit(1);
            }
            return Return;
        }
        MyValue result = value->exec(node);
        if (result.type != method->getReturnType()) {
            cout << "Error:" << method->Id << ": return value does not match the function type" << endl;
            exit(1);
        }
        method->setReturnValue(result);
        return Return;
    }
};

class Constant : public MyExpr {
private:
    MyValue value;
public:
    Constant(MyValue value)
    {
        this->value = value;
    }

    virtual MyValue exec(Node* node)
    {
        return value;
    }
};

class VarExpr : public MyExpr {
private:
    string Id;
public:
    VarExpr(const char* name)
    {
        this->Id = name;
    }

    MyValue exec(Node* node) { return node->getVar(Id).value; }
};

bool equalsVar(MyValue first, MyValue second);

class BinExpr : public MyExpr {
private:
    MyExpr* arg1;
    MyExpr* arg2;
    operation type;
    bool checkTypes(MyValue val1, MyValue val2) {
        switch (type)
        {
            case Add: case Sub: case Mul: case Div: case Mod:
            { return val1.type == val2.type && val1.type == Int; }
            case And: case Or:
            { return val1.type == val2.type && val1.type == Bool; }
            case Equals: case NotEquals:
            {   return val1.type == val2.type; }
            case Less: case Greater:  case LessEquals: case GreaterEquals:
            { return val1.type == val2.type && val1.type == Int; }
            default: { return false; }
        }
    }

public:
    BinExpr(operation type, MyExpr* arg1, MyExpr* arg2) : type(type), arg1(arg1), arg2(arg2) {}

    MyValue exec(Node* node) {
        MyValue val1 = arg1->exec(node);
        MyValue val2 = arg2->exec(node);

        checkTypes(val1, val2);

        MyValue result;
        switch (type)
        {
            case Add: { result.type = Int; result.int_value = val1.int_value + val2.int_value; break; }
            case Sub: { result.type = Int; result.int_value = val1.int_value - val2.int_value; break; }
            case Mul: { result.type = Int; result.int_value = val1.int_value * val2.int_value; break; }
            case Div: { result.type = Int; result.int_value = val1.int_value / val2.int_value; break; }
            case Mod: { result.type = Int; result.int_value = val1.int_value % val2.int_value; break; }
            case And: { result.type = Bool; result.bool_value = val1.bool_value && val2.bool_value; break; }
            case Or:  { result.type = Bool; result.bool_value = val1.bool_value || val2.bool_value; break; }
            case Equals: { result.type = Bool; result.bool_value = equalsVar(val1, val2); break; }
            case NotEquals: { result.type = Bool; result.bool_value = !equalsVar(val1, val2); break; }
            case Less: { result.type = Bool; result.bool_value = val1.int_value < val2.int_value; break; }
            case Greater: { result.type = Bool; result.bool_value = val1.int_value > val2.int_value; break; }
            case LessEquals: { result.type = Bool; result.bool_value = val1.int_value <= val2.int_value; break; }
            case GreaterEquals: { result.type = Bool; result.bool_value = val1.int_value >= val2.int_value; break; }
            default: { break; }
        }
        return result;
    }
};

class ParamList {
private:
    vector<MyExpr*> params;
public:
    ParamList() {}

    int size()
    {
        return params.size();
    }

    MyExpr* getAt(int index)
    {
        if (index >= params.size())
        {
            return NULL;
        }
        return params[index];
    }

    void add(MyExpr* expr)
    {
        params.push_back(expr);
    }
};

class InvocExpr : public MyExpr {
private:
    ParamList* params;
    string methodId;
    MainClass* main;
public:
    InvocExpr(ParamList* params, const char* methodName, MainClass* main): params(params), methodId(methodName), main(main) {}

    MyValue exec(Node* node) {
        Method* method = main->getMethod(methodId);
        if (method == NULL) {
            cout << "Error: " << methodId << ": method not found" << endl;
            exit(1);
        }
        method->setNode(new Node(main->getNode()));

        for(int i = 0; i < params->size(); ++i) {
            MyValue value = params->getAt(i)->exec(node);
            method->addArg(value);
        }
        return method->run();
    }
};

class IfStatement : public Statement {
private:
    Statement* Then;
    Statement * Else;
    MyExpr* expr;
public:
    IfStatement(MyExpr* expr, Statement* Then, Statement* Else = NULL) : expr (expr), Then(Then), Else (Else) {}

    InterruptionType execute(Node* node) {
        MyValue expre = expr->exec(node);
        if (expre.type != Bool) {
            cout << "Error: expected boolean expression in if" << endl;
            exit(1);
        }

        return (expre.bool_value == true) ? Then->execute(node) : (Else != NULL)? Else->execute(node) : NoIterruption;
    }
};

class WhileStatement : public Statement {
private:
    MyExpr* expr;
    Statement* body;
public:
    WhileStatement(MyExpr* condition, Statement* body): expr(condition), body(body) {}
    InterruptionType execute(Node* node) {
        MyValue val = expr->exec(node);
        if (val.type != Bool) {
            cout << "Error: expected boolean expression in while" << endl;
            exit(1);
        }

        InterruptionType result = NoIterruption;

        while(val.bool_value == true)
        {
            result = body->execute(node);
            if (result != NoIterruption)
            {
                break;
            }
            val = expr->exec(node);
        }
        return  (result == Return) ? Return : NoIterruption;
    }
};

class BreakStatement : public Statement {
    InterruptionType execute(Node* node) { return Break; }
};

class InvokeStatement : public Statement {
private:
    MyExpr* expre;
public:
    InvokeStatement(MyExpr* expre): expre (expre) {};
    InterruptionType execute(Node* node) {  expre->exec(node);  return NoIterruption; }
};

//#include "java.tab.hpp"

#endif //MINIJAVACOMPILER_JAVAHELP_H
