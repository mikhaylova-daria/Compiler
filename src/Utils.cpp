//
// Created by nicolai on 29.09.15.
//

#include "JavaHelp.h"
#include <vector>
#include <string>
#include <cstring>
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

const char* toString(VarType type)
{
    switch (type) {
        case Int: return "int";
        case Bool: return "boolean";
        case NoType: return "undefined type";
        default: return NULL;
    }
}

const char* toString(MyValue value)
{
    char* result = new char[256];
    switch (value.type)
    {
        case Int: { sprintf(result, "%d", value.int_value); break; }
        case Bool: { strcpy(result, value.bool_value ? "true" : "false"); }
        default: break;
    }
    return result;
}

ArgumentList*  makeList(int count, ...)
{
    ArgumentList* list = new ArgumentList();
    va_list args;
    va_start(args, count);
    ostringstream oss;
    string var = oss.str();
    for(int index = 0; index < count; ++index)
    {
        VarType type = (VarType)va_arg(args, int);
        oss << "arg" << index;
        Argument* arg = new Argument(oss.str(), type);
        list->add(arg);
        oss.clear();
    }
    va_end(args);
    return list;
}

int parseInt(const string & st)
{
    int result;
    istringstream(st) >> result;
    return result;
}

bool parseBool(const string & st)
{
    string copy = st;
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return st == "true";
}

bool equalsVar(MyValue first, MyValue second)
{
    return memcmp(&first, &second, sizeof(MyValue)) == 0;
}


