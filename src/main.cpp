#include <cstdio>

extern "C" {
    int yylex();
}

extern "C" FILE* yyin;

extern int yyparse();

#include "iostream"
#include "JavaHelp.h"

extern MainClass mainClass;

using namespace std;

int main(int argc, const char* argv[])
{
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