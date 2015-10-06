#include <cstdio>
#include <fstream>

extern "C" {
    int yylex();
}

extern "C" FILE* yyin;

extern int yyparse();

#include "iostream"
#include "JavaHelp.h"

extern MainClass mainClass;

using namespace std;

vector<string> text;

void printTextPart(Location loc) {
    if (loc.firstLine == loc.lastLine)
        cout << text[loc.firstLine].substr(loc.firstColumn, loc.lastColumn - loc.firstColumn) << endl;
    else {
        //cout << text[loc.firstColumn].size() << endl;
        for (int i = 0; i < loc.firstColumn; i++)
            cout << ' ';
        cout << text[loc.firstLine].substr(loc.firstColumn, text[loc.firstLine].size() - loc.firstColumn) << endl;
        for (int i = loc.firstLine + 1; i < loc.lastLine; i++)
            cout << text[i] << endl;
        cout << text[loc.lastLine].substr(0, loc.lastColumn) << endl;
    }
}

int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);
    string line;
    while (getline(in, line))
        text.push_back(line);

    yyin = fopen(argv[1], "r");
    for(int i = 2; i < argc; ++i)
    {
        mainArgs.push_back(argv[i]);
    }
    yyparse();
    mainClass.run();
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