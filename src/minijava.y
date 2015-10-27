%locations
%{

    #include "JavaHelp.h"
    #include "MinijavaTree.h"
    //#define YYLTYPE Location

    #include "Declaration.h"
    #include "tokens.h"
    #include <vector>
    #include <iostream>
    #include <string>
    using namespace std;

    string error_msg;

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
| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' error ')' '{' STATEMENT '}' '}' { processRule(@$, "MAIN_CLASS"); }
| CLASS ID '{' error MAIN '(' MAIN_ARGS ID ')' '{' STATEMENT '}' '}' { processRule(@$, "MAIN_CLASS"); }

CLASS_DECLARATION : CLASS ID BASE_CLASS '{' VAR_AND_METHOD_DECLARATION '}' { processRule(@$, "CLASS_DECLARATION"); }

BASE_CLASS : { processRule(@$, "BASE_CLASS"); }
| EXTENDS ID { processRule(@$, "BASE_CLASS"); }

VAR_AND_METHOD_DECLARATION : VAR_DECLARATION VAR_AND_METHOD_DECLARATION { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }
| METHOD_DECLARATION VAR_AND_METHOD_DECLARATION { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }
| { processRule(@$, "VAR_AND_METHOD_DECLARATION"); }

VAR_DECLARATION : TYPE ID ';'  { processRule(@$, "VAR_DECLARATION"); }
| error ID ';' { processRule(@$, "VAR_DECLARATION"); }

METHOD_DECLARATION: METHOD_HEADER '{' METHOD_BODY '}' { processRule(@$, "METHOD_DECLARATION"); }

METHOD_HEADER : PUBLIC TYPE ID '(' ARGS_DECLARATION ')' { processRule(@$, "METHOD_HEADER"); }
| PUBLIC TYPE ID '(' error ')' { processRule(@$, "METHOD_HEADER"); }
| error ID '(' ARGS_DECLARATION ')' { processRule(@$, "METHOD_HEADER"); }

ARGS_DECLARATION : PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); }
| ARGS_DECLARATION ',' PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); }

PARAM_DECLARATION : TYPE ID { processRule(@$, "PARAM_DECLARATION"); }
| { processRule(@$, "PARAM_DECLARATION"); }

TYPE : INT_ARRAY { processRule(@$, "INT_ARRAY"); }
| BOOL { processRule(@$, "TYPE"); }
| INT { processRule(@$, "TYPE"); }
| ID { processRule(@$, "TYPE"); }

INT_ARRAY: INT '[' ']' { processRule(@$, "INT_ARRAY"); }
| INT '[' error ']' { processRule(@$, "INT_ARRAY"); }

METHOD_BODY : VAR_AND_STATEMENT_DECLARATIONS RETURN EXPR ';' { processRule(@$, "METHOD_BODY"); }

VAR_AND_STATEMENT_DECLARATIONS : VAR_DECLARATION VAR_AND_STATEMENT_DECLARATIONS { processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS"); }
| STATEMENT_DECLARATION {
    processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS");
    $$ = $1;
}

STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION {
    processRule(@$, "STATEMENT_DECLARATION");
    $$ = new CStatementList(getLocation(), $1, $2)
}
| {
    processRule(@$, "STATEMENT_DECLARATION");
    $$ = nullptr;
}

STATEMENT : '{' STATEMENT_DECLARATION '}' {
    processRule(@$, "STATEMENT");
    $$ = new CBracketStatement(getLocation(), $2);
}
| IF_STATEMENT {
    processRule(@$, "STATEMENT");
    $$ = $1;
}
| WHILE_STATEMENT {
    processRule(@$, "STATEMENT");
    $$ = $1;
}
| PRINT_STATEMENT {
    processRule(@$, "STATEMENT");
    $$ = $1;
}
| ASSIGNMENT {
    processRule(@$, "STATEMENT");
    $$ = $1;
}
| ARRAY_ASSIGNMENT {
    processRule(@$, "STATEMENT");
    $$ = $1;
}

IF_STATEMENT : IF '(' EXPR ')' STATEMENT ELSE STATEMENT {
    processRule(@$, "IF_STATEMENT");
    $$ = new CIfStatement(getLocation(), $3, $5, $7);
}
| IF '(' error ')' STATEMENT ELSE STATEMENT {
    processRule(@$, "IF_STATEMENT");
    delete $5;
    delete $7;
    $$ = nullptr;
}
| IF '(' EXPR ')' error ELSE STATEMENT {
    processRule(@$, "IF_STATEMENT");
    delete $3;
    delete $7;
    $$ = nullptr;
}
| IF '(' EXPR ')' STATEMENT ELSE error {
    processRule(@$, "IF_STATEMENT");
    delete $3;
    delete $5;
    $$ = nullptr;
}

WHILE_STATEMENT : WHILE '(' EXPR ')' STATEMENT {
    processRule(@$, "WHILE_STATEMENT");
    $$ = CWhileStatement(getLocation(), $3, $5);
}
| WHILE '(' error ')' STATEMENT {
    processRule(@$, "WHILE_STATEMENT");
    $$ = nullptr;
}

PRINT_STATEMENT : PRINT '(' EXPR ')' ';' {
    processRule(@$, "PRINT_STATEMENT");
    $$ = CPrintStatement(getLocation(), $3);
}
| PRINT '(' error ')' ';' {
    processRule(@$, "PRINT_STATEMENT");
    $$ = nullptr;
}

ASSIGNMENT : ID '=' EXPR ';' {
    processRule(@$, "ASSIGNMENT");
    $$ = new CAssignmentExpression(getLocation(), $3, $1);
}
| ID '=' error ';' {
    processRule(@$, "ASSIGNMENT");
    delete $1;
    $$ = nullptr;
}

ARRAY_ASSIGNMENT : ID '[' EXPR ']' '=' EXPR ';' {
    processRule(@$, "ARRAY_ASSIGNMENT");
    $$ = CIntArrayAssignmentExpression(getLocation(), $3, $6, $1);
}
| ID '[' error ']' '=' EXPR ';' {
    processRule(@$, "ARRAY_ASSIGNMENT");
    delete $1;
    delete $6;
    $$ = nullptr;
}
| ID '[' EXPR ']' '=' error ';' {
    processRule(@$, "ARRAY_ASSIGNMENT");
    delete $1;
    delete $3;
    $$ = nullptr;
}

EXPR :
  EXPR '+' EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_PLUS);
}
| EXPR '-' EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_MINUS);
}
| EXPR '*' EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_MULTIPLICATION);
}
| EXPR AND EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_AND);
}
| EXPR '<' EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_LESS);
}
| EXPR EQ EXPR {
    processRule(@$, "EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_EQ);
}
| NOT EXPR {
    processRule(@$, "EXPR");
    $$ = new CNotExpression(getLocation(), $2);
}
| '(' EXPR ')' {
    processRule(@$, "EXPR");
    $$ = new CLengthExpression(getLocation(), $2);
}
| NEW_EXPR {
    processRule(@$, "EXPR");
    $$ = $1;
}
| ID {
    processRule(@$, "EXPR");
    $$ = new CIdentifier(getLocation(), yytext);
}
| THIS {
    processRule(@$, "EXPR");
    $$ = new CThisIdentifier(getLocation());
}
| CONSTANT {
    processRule(@$, "EXPR");
    $$ = $1;
}
| EXPR '[' EXPR ']' {
    processRule(@$, "INVOKE_EXPR");
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_SQ_BRACKETS);
}
| EXPR '[' error ']' {
    processRule(@$, "INVOKE_EXPR");
    $$ = 0;
}
| EXPR '.' LENGTH {
    processRule(@$, "INVOKE_EXPR");
    $$ = new CLengthExpression(getLocation(), $1);
}
| EXPR '.' ID '(' PARAMS ')' {
    processRule(@$, "INVOKE_EXPR");
    $$ = new CInvocation(getLocation(), $1, $3, $5);
}
| EXPR '.' ID '(' error ')' {
    processRule(@$, "INVOKE_EXPR");
    $$ = 0;
}

CONSTANT : INT_VALUE {
    processRule(@$, "CONSTANT");
    $$ = new CConstant(getLocation(), CT_INT, yytext);
}
| BOOL_VALUE {
    processRule(@$, "CONSTANT");
    $$ = new CConstant(getLocation(), CT_BOOL, yytext);
}



PARAMS : {
    processRule(@$, "PARAMS");
    $$ = 0;
}
| EXPR {
    processRule(@$, "PARAMS");
    $$ = CExpressionList(getLocation(), $1, 0);
}
| PARAMS ',' EXPR {
    processRule(@$, "PARAMS");
    $$ = CExpressionList(getLocation(), $3, $1);
}

NEW_EXPR :
NEW INT '[' EXPR ']' {
    processRule(@$, "NEW_EXPR");
    $$ = new CIntArrayNewExpression(getLocation(), $4);
}
| NEW INT '[' error ']' {
    processRule(@$, "NEW_EXPR");
    $$ = 0;
}
| NEW ID '(' ')' {
    processRule(@$, "NEW_EXPR");
    $$ = new CNewExpression(getLocation(), new CIdentifier(yytext));
}
| NEW ID '(' error ')' {
    processRule(@$, "NEW_EXPR");
    $$ = 0;
}

%%

extern void printError(Location location, const char *s);
void yyerror(const char *s)
{
    printError(Location(yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column), s);
}
extern int main(int argc, const char* argv[]);