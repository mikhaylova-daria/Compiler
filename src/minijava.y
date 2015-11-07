%locations
%{

    #include "tree/MinijavaTree.h"
    #include "tree/TreeBuildHelp.h"

    #include "tokens.h"

    #include <vector>
    #include <iostream>
    #include <string>
    #include <memory>
    using namespace std;

    #include "symbol/Symbol.h"
    using namespace Symbol;

    extern CStorage globalStorage;

    string error_msg;

    int yylex();
    void yyerror(const char *);

    extern int yylineno;
    extern FILE * yyin;
    extern char* yytext;


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

    std::shared_ptr<CGoal> Goal;
%}

%union {
    IExpression* expression;
    CExpressionList* expressionList;
    CConstant* constant;
    IStatement* statement;
    CStatementList* statementList;
    CMethodBodyDeclaration* methodBodyDeclaration;
    CType* type;
    CVarDeclaration* varDeclaration;
    CMethodArgumentsList* methodArgumentsList;
    CMethodHeaderDeclaration* methodHeaderDeclaration;
    CMethodDeclaration* methodDeclaration;
    CMethodDeclarationList* methodDeclarationList;
    CIdentifier* identifier;
    CClassDeclaration* classDeclaration;
    CMainClass* mainClass;
    CClassDeclarationList* classDeclarationList;

    TVarAndStatementDeclaration varAndStatementDeclaration;
    TVarAndMethodDeclaration varAndMethodDeclaration;
};

%type <expression> NEW_EXPR EXPR
%type <expressionList> PARAMS
%type <constant> CONSTANT
%type <statement> ARRAY_ASSIGNMENT ASSIGNMENT PRINT_STATEMENT WHILE_STATEMENT IF_STATEMENT STATEMENT
%type <statementList> STATEMENT_DECLARATION
%type <varAndStatementDeclaration> VAR_AND_STATEMENT_DECLARATIONS
%type <varAndMethodDeclaration> VAR_AND_METHOD_DECLARATION
%type <methodBodyDeclaration> METHOD_BODY
%type <type> INT_ARRAY TYPE
%type <varDeclaration> PARAM_DECLARATION VAR_DECLARATION
%type <methodArgumentsList> ARGS_DECLARATION
%type <methodHeaderDeclaration> METHOD_HEADER
%type <methodDeclaration> METHOD_DECLARATION
%type <methodDeclarationList> METHOD_DECLARATION_LIST
%type <identifier> ID BASE_CLASS
%type <classDeclaration> CLASS_DECLARATION
%type <mainClass> MAIN_CLASS
%type <classDeclarationList> CLASS_LIST

%token MAIN MAIN_ARGS PUBLIC VOID STATIC CLASS RETURN WHILE PRINT LENGTH NEW EXTENDS THIS

%token INT BOOL

%token INT_VALUE BOOL_VALUE

%left AND EQ NOT
%left '+' '-' '.' '<'
%left '*'
%nonassoc _ID
%nonassoc '['
%nonassoc IF
%nonassoc ELSE

%%

GOAL : MAIN_CLASS CLASS_LIST {
    processRule(@$, "GOAL");
    Goal = std::shared_ptr<CGoal>(new CGoal(getLocation(), $1, $2));
}

CLASS_LIST : CLASS_DECLARATION CLASS_LIST {
    processRule(@$, "CLASS_LIST");
    $$ = new CClassDeclarationList(getLocation(), $1, $2);
}
| {
    processRule(@$, "ARGS_DECLARATION");
    $$ = nullptr;
}

MAIN_CLASS : CLASS ID '{' PUBLIC STATIC VOID MAIN '(' MAIN_ARGS ID ')' '{' STATEMENT '}' '}' {
    processRule(@$, "MAIN_CLASS");
    $$ = new CMainClass(getLocation(), $2, $10, $13);
}
| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' error ')' '{' STATEMENT '}' '}' {
    processRule(@$, "MAIN_CLASS");
    delete $2;
    delete $12;
    $$ = nullptr;
}
| CLASS ID '{' error MAIN '(' MAIN_ARGS ID ')' '{' STATEMENT '}' '}' {
    processRule(@$, "MAIN_CLASS");
    delete $2;
    delete $8;
    delete $11;
    $$ = nullptr;
}

CLASS_DECLARATION : CLASS ID BASE_CLASS '{' VAR_AND_METHOD_DECLARATION '}' {
    processRule(@$, "CLASS_DECLARATION");
    $$ = new CClassDeclaration(getLocation(), $2, $3, $5.varDeclList, $5.methodDeclList);
}

BASE_CLASS : {
    processRule(@$, "BASE_CLASS");
    $$ = nullptr;
}
| EXTENDS ID {
    processRule(@$, "BASE_CLASS");
    $$ =  $2;
}

VAR_AND_METHOD_DECLARATION : VAR_DECLARATION VAR_AND_METHOD_DECLARATION {
    processRule(@$, "VAR_AND_METHOD_DECLARATION");
    $2.varDeclList = new CVarDeclarationList(getLocation(), $1, $2.varDeclList);
}
| METHOD_DECLARATION_LIST {
    $$.varDeclList = nullptr;
    $$.methodDeclList = $1;
}

METHOD_DECLARATION_LIST : METHOD_DECLARATION METHOD_DECLARATION_LIST {
    $$ = new CMethodDeclarationList(getLocation(), $1, $2);
}
| {
    $$ = nullptr;
}

VAR_DECLARATION : TYPE ID ';'  {
    processRule(@$, "VAR_DECLARATION");
    $$ = new CVarDeclaration(getLocation(), $1, $2);
}
| error ID ';' {
    processRule(@$, "VAR_DECLARATION");
    delete $2;
    $$ = nullptr;
}

METHOD_DECLARATION: METHOD_HEADER '{' METHOD_BODY '}' {
    processRule(@$, "METHOD_DECLARATION");
    $$ = new CMethodDeclaration(getLocation(), $1, $3);
}

METHOD_HEADER : PUBLIC TYPE ID '(' ARGS_DECLARATION ')' {
    processRule(@$, "METHOD_HEADER");
    $$ = new CMethodHeaderDeclaration(getLocation(), $2, $3, $5);
}
| PUBLIC TYPE ID '(' error ')' {
    processRule(@$, "METHOD_HEADER");
    delete $2;
    delete $3;
    $$ = nullptr;
}
| error ID '(' ARGS_DECLARATION ')' {
    processRule(@$, "METHOD_HEADER");
    delete $2;
    delete $4;
    $$ = nullptr;
}

ARGS_DECLARATION : {
    processRule(@$, "ARGS_DECLARATION");
    $$ = nullptr;
}
| PARAM_DECLARATION ',' ARGS_DECLARATION {
    processRule(@$, "ARGS_DECLARATION");
    $$ = new CMethodArgumentsList(getLocation(), $1, $3);
}

PARAM_DECLARATION : TYPE ID {
    processRule(@$, "PARAM_DECLARATION");
    $$ = new CVarDeclaration(getLocation(), $1, $2);
}

TYPE : INT_ARRAY {
    processRule(@$, "INT_ARRAY");
    $$ = $1;
}
| BOOL {
    processRule(@$, "TYPE");
    $$ = new CType(getLocation(), T_BOOL, globalStorage.Get("boolean"));
}
| INT {
    processRule(@$, "TYPE");
    $$ = new CType(getLocation(), T_INT, globalStorage.Get("int"));
}
| ID {
    processRule(@$, "TYPE");
    $$ = new CType(getLocation(), T_CLASS, $1->Symbol);
    delete $1;
}

INT_ARRAY: INT '[' ']' {
    processRule(@$, "INT_ARRAY");
    $$ = new CType(getLocation(), T_INT_ARRAY, globalStorage.Get("int[]"));
}
| INT '[' error ']' {
    processRule(@$, "INT_ARRAY");
    $$ = nullptr;
}

METHOD_BODY : VAR_AND_STATEMENT_DECLARATIONS RETURN EXPR ';' {
    processRule(@$, "METHOD_BODY");
    $$ = new CMethodBodyDeclaration(getLocation(), $1.varDeclList, $1.statementList, $3);
}

VAR_AND_STATEMENT_DECLARATIONS : VAR_DECLARATION VAR_AND_STATEMENT_DECLARATIONS {
    processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS");
    $2.varDeclList = new CVarDeclarationList(getLocation(), $1, $2.varDeclList);
    $$ = $2;
}
| STATEMENT_DECLARATION {
    processRule(@$, "VAR_AND_STATEMENT_DECLARATIONS");
    $$.statementList = $1;
    $$.varDeclList = nullptr;
}

STATEMENT_DECLARATION : STATEMENT STATEMENT_DECLARATION {
    processRule(@$, "STATEMENT_DECLARATION");
    $$ = new CStatementList(getLocation(), $1, $2);
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
    $$ = new CWhileStatement(getLocation(), $3, $5);
}
| WHILE '(' error ')' STATEMENT {
    processRule(@$, "WHILE_STATEMENT");
    $$ = nullptr;
}

PRINT_STATEMENT : PRINT '(' EXPR ')' ';' {
    processRule(@$, "PRINT_STATEMENT");
    $$ = new CPrintStatement(getLocation(), $3);
}
| PRINT '(' error ')' ';' {
    processRule(@$, "PRINT_STATEMENT");
    $$ = nullptr;
}

ASSIGNMENT : ID '=' EXPR ';' {
    processRule(@$, "ASSIGNMENT");
    $$ = new CAssignmentStatement(getLocation(), $3, $1);
}
| ID '=' error ';' {
    processRule(@$, "ASSIGNMENT");
    delete $1;
    $$ = nullptr;
}

ARRAY_ASSIGNMENT : ID '[' EXPR ']' '=' EXPR ';' {
    processRule(@$, "ARRAY_ASSIGNMENT");
    $$ = new CIntArrayAssignmentStatement(getLocation(), $3, $6, $1);
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
    $$ = new CBinaryExpression(getLocation(), $1, $3, BE_EQUAL);
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
    $$ = new CVariable(getLocation(), $1);
}
| THIS {
    processRule(@$, "EXPR");
    $$ = new CVariable(getLocation(), new CIdentifier(getLocation(), globalStorage.Get("this")));
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
    $$ = new CConstant(getLocation(), T_INT, yytext);
}
| BOOL_VALUE {
    processRule(@$, "CONSTANT");
    $$ = new CConstant(getLocation(), T_BOOL, yytext);
}


PARAMS : {
    processRule(@$, "PARAMS");
    $$ = 0;
}
| EXPR {
    processRule(@$, "PARAMS");
    $$ = new CExpressionList(getLocation(), $1, 0);
}
| PARAMS ',' EXPR {
    processRule(@$, "PARAMS");
    $$ = new CExpressionList(getLocation(), $3, $1);
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
    $$ = new CNewExpression(getLocation(), $2);
}
| NEW ID '(' error ')' {
    processRule(@$, "NEW_EXPR");
    $$ = 0;
}

ID : _ID {
    processRule(@$, "NEW_EXPR");
    $$ = new CIdentifier(getLocation(), globalStorage.Get(yytext));
}

%%

extern void printError(Location location, const char *s);
void yyerror(const char *s)
{
    printError(Location(yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column), s);
}
extern int main(int argc, const char* argv[]);