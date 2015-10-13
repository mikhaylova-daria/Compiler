%locations
%{

    #include "JavaHelp.h"
    //#define YYLTYPE Location

    #include "Declaration.h"
    #include "tokens.h"
    #include <vector>
    #include <iostream>
    #include <string>
    using namespace std;


    int yylex();
    void yyerror(const char *);

    extern int yylineno;
    extern FILE * yyin;

    extern void printTextPart(Location loc, ostream &out = std::cout);
    Location currLocation;
    Location getLocation() {
        return currLocation;
    }
    void setLocation(YYLTYPE loc) {
        currLocation = Location(loc.first_line, loc.first_column, loc.last_line, loc.last_column);
    }
    void processRule(YYLTYPE loc, const char* ruleName) {
        setLocation(loc);
        printf("%s ", ruleName);
        currLocation.print();
        printTextPart(currLocation);
    }

%}

%token MAIN MAIN_ARGS PUBLIC VOID STATIC CLASS RETURN WHILE PRINT LENGTH NEW EXTENDS THIS

%token INT BOOL
%token ID

%token INT_VALUE BOOL_VALUE

%left OR AND GE LE GT LT EQ NEQ NOT
%left '+' '-' '.'
%left '*' '/' '%'
%nonassoc ID
%nonassoc '['
%nonassoc IF
%nonassoc ELSE

%%

GOAL : MAIN_CLASS CLASS_LIST { processRule(@$, "GOAL"); }

CLASS_LIST : CLASS_LIST CLASS_DECLARATION { processRule(@$, "CLASS_LIST"); }
| { processRule(@$, "ARGS_DECLARATION"); }

MAIN_CLASS : CLASS ID '{' PUBLIC STATIC VOID MAIN '(' MAIN_ARGS ID ')' '{' STATEMENT '}' '}' { processRule(@$, "MAIN_CLASS"); }

CLASS_DECLARATION : CLASS ID BASE_CLASS '{' VAR_AND_METHOD_DECLARATION '}' { processRule(@$, "CLASS_DECLARATION"); }

BASE_CLASS : { processRule(@$, "BASE_CLASS"); }
| EXTENDS ID { processRule(@$, "BASE_CLASS"); }

VAR_AND_METHOD_DECLARATION : VAR_DECLARATION VAR_AND_METHOD_DECLARATION { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }
| METHOD_DECLARATION VAR_AND_METHOD_DECLARATION { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }
| { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }

VAR_DECLARATION : TYPE ID ';'  { processRule(@$, "VAR_DECLARATION"); }

METHOD_DECLARATION: METHOD_HEADER '{' METHOD_BODY '}' { processRule(@$, "METHOD_DECLARATION"); }

METHOD_HEADER : PUBLIC TYPE ID '(' ARGS_DECLARATION ')' { processRule(@$, "METHOD_HEADER"); }

ARGS_DECLARATION : PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); }
| ARGS_DECLARATION ',' PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); }

PARAM_DECLARATION : TYPE ID { processRule(@$, "PARAM_DECLARATION"); }
| { processRule(@$, "PARAM_DECLARATION"); }

TYPE : INT_ARRAY { processRule(@$, "INT_ARRAY"); }
| BOOL { processRule(@$, "TYPE"); }
| INT { processRule(@$, "TYPE"); }
| ID { processRule(@$, "TYPE"); }

INT_ARRAY: INT '[' ']' { processRule(@$, "INT_ARRAY"); }

METHOD_BODY : VAR_AND_STATEMENT_DECLARATIONS RETURN EXPR ';' { processRule(@$, "METHOD_BODY"); }

VAR_AND_STATEMENT_DECLARATIONS : VAR_DECLARATION VAR_AND_STATEMENT_DECLARATIONS { processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS"); }
| STATEMENT_DECLARATION { processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS"); }

STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION { processRule(@$, "STATEMENT_DECLARATION"); }
| { processRule(@$, "STATEMENT_DECLARATION"); }

STATEMENT : '{' STATEMENT_DECLARATION '}' { processRule(@$, "STATEMENT"); }
| IF_STATEMENT { processRule(@$, "STATEMENT"); }
| WHILE_STATEMENT { processRule(@$, "STATEMENT"); }
| PRINT_STATEMENT { processRule(@$, "STATEMENT"); }
| ASSIGNMENT { processRule(@$, "STATEMENT"); }
| ARRAY_ASSIGNMENT { processRule(@$, "STATEMENT"); }

IF_STATEMENT : IF '(' EXPR ')' STATEMENT ELSE STATEMENT { processRule(@$, "IF_STATEMENT"); }
WHILE_STATEMENT : WHILE '(' EXPR ')' STATEMENT { processRule(@$, "WHILE_STATEMENT"); }
PRINT_STATEMENT : PRINT '(' EXPR ')' ';' { processRule(@$, "PRINT_STATEMENT"); }
ASSIGNMENT : ID '=' EXPR ';' { processRule(@$, "ASSIGNMENT"); }
ARRAY_ASSIGNMENT : ID '[' EXPR ']' '=' EXPR ';' { processRule(@$, "ARRAY_ASSIGNMENT"); }

EXPR :
  EXPR '+' EXPR { processRule(@$, "EXPR"); }
| EXPR '-' EXPR { processRule(@$, "EXPR"); }
| EXPR '/' EXPR { processRule(@$, "EXPR"); }
| EXPR '%' EXPR { processRule(@$, "EXPR"); }
| EXPR '*' EXPR { processRule(@$, "EXPR"); }
| EXPR AND EXPR { processRule(@$, "EXPR"); }
| EXPR OR EXPR { processRule(@$, "EXPR"); }
| EXPR LT EXPR { processRule(@$, "EXPR"); }
| EXPR LE EXPR { processRule(@$, "EXPR"); }
| EXPR GT EXPR { processRule(@$, "EXPR"); }
| EXPR GE EXPR { processRule(@$, "EXPR"); }
| EXPR NEQ EXPR { processRule(@$, "EXPR"); }
| EXPR EQ EXPR { processRule(@$, "EXPR"); }
| NOT EXPR { processRule(@$, "EXPR"); }
| '(' EXPR ')' { processRule(@$, "EXPR"); }
| NEW_EXPR { processRule(@$, "EXPR"); }
| ID { processRule(@$, "EXPR"); }
| THIS { processRule(@$, "EXPR"); }
| CONSTANT { processRule(@$, "EXPR"); }
| EXPR '[' EXPR ']' { processRule(@$, "INVOKE_EXPR"); }
| EXPR '.' LENGTH { processRule(@$, "INVOKE_EXPR"); }
| EXPR '.' ID '(' PARAMS ')' { processRule(@$, "INVOKE_EXPR"); }

CONSTANT : INT_VALUE | BOOL_VALUE { processRule(@$, "CONSTANT"); }



PARAMS : { processRule(@$, "PARAMS"); }
| EXPR { processRule(@$, "PARAMS"); }
| PARAMS ',' EXPR { processRule(@$, "PARAMS"); }

NEW_EXPR : NEW INT '[' EXPR ']' { processRule(@$, "NEW_EXPR"); }
| NEW ID '(' ')' { processRule(@$, "NEW_EXPR"); }

%%

extern void printError(Location location, const char *s);
void yyerror(const char *s)
{
    printError(Location(yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column), s);
}
extern int main(int argc, const char* argv[]);