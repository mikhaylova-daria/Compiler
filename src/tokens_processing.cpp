#include <iostream>
#include <cstring>
using namespace std;

static int lineNumber = 0;
static int linePosition = 0;


void processToken(const char* token, const char* yytext) {
    cout << token << '[' << lineNumber << ',' << linePosition << ']' << endl;
    linePosition += strlen(yytext);
}
void processValue(const char* token, const char* yytext) {
    cout << token << '(' << yytext << ')';
    cout << '[' << lineNumber << ',' << linePosition << ']' << endl;
    linePosition += strlen(yytext);
}
void processNewLine(const char* yytext) {
    lineNumber += strlen(yytext);
    linePosition = 0;
}
void processSpace(const char* yytext) {
    linePosition += strlen(yytext);
}
void processErrorToken(const char* yytext) {
    cerr << "ERROR: unexpected token '" << yytext << "' at line " << lineNumber << " in position " << linePosition;
    cerr << std::endl;
}

