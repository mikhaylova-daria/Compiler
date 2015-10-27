#include <cstdio>
#include <fstream>

extern "C" {
    int yylex();
}

extern "C" FILE* yyin;

extern int yyparse();

#include <iostream>
#include <vector>
#include "JavaHelp.h"
#include "tokens.h"

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
    return 0;
}

/*
int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "USING: mjc filename";
        return -1;
    }
    freopen(argv[1], "r", stdin);
    return yyparse();
}
 */