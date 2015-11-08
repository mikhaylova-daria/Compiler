#include <cstdio>
#include <fstream>
#include <iostream>
#include "symbol/Symbol.h"
#include "tree/MinijavaTree.h"
#include "visitors/CPrinter2.hpp"
#include "visitors/type_checking/TypeChecker.h"
#include "visitors/type_checking/SymbolTableBuilder.h"

Symbol::CStorage globalStorage;
extern std::shared_ptr<CGoal> Goal;

extern "C" {
    int yylex();
}

extern "C" FILE* yyin;

extern int yyparse();

using namespace std;

vector<string> text;

void printTextPart(Location loc, ostream &out = std::cout)
{
    loc.firstColumn--; loc.firstLine--; loc.lastColumn--; loc.lastLine--;
    if (loc.firstLine == loc.lastLine) {
        out << text[loc.firstLine].substr(loc.firstColumn, loc.lastColumn - loc.firstColumn) << endl;
    } else {
        //cout << text[loc.firstColumn].size() << endl;
        for (int i = 0; i < loc.firstColumn; i++)
            out << ' ';
        out << text[loc.firstLine].substr(loc.firstColumn, text[loc.firstLine].size() - loc.firstColumn) << endl;
        for (int i = loc.firstLine + 1; i < loc.lastLine; i++)
            out << text[i] << endl;
        out << text[loc.lastLine].substr(0, loc.lastColumn) << endl;
    }
}

void printError(Location location, const char *s)
{
    std::cerr << "error in position (" << location.lastLine << ' ' << location.firstColumn << ' ';
    std::cerr << location.lastLine << ' ' << location.lastColumn << "): " << s << " : ";
    printTextPart(location, std::cerr);
}


int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);
    string line;
    while (getline(in, line))
        text.push_back(line);

    yyin = fopen(argv[1], "r");
    yyparse();
    CPrinter2 printer2;
    printer2.Visit(Goal.get());
    CTable table;
    CSymbolTableBuilder symbolTableBuilder(table, globalStorage);
    symbolTableBuilder.Visit(Goal.get());
    if (symbolTableBuilder.IsError()) {
        std::cout << "type error" << std::endl;
        return -1;
    }
    CTypeChecker typeChecker(table, globalStorage);
    typeChecker.Visit(Goal.get());
    if (typeChecker.IsError()) {
        std::cout << "type error" << std::endl;
        return -1;
    }
    return 0;
}
