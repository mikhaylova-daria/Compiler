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

    extern void printTextPart(Location loc);
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

    vector<string> mainArgs;
    string mainArgsId;
    MainClass mainClass;
    Library library;
    VarType curType;
    Method* curMethod;
%}


%union {
    Method* method;
    MyExpr* expr;
    ArgumentList* args;
    Argument* arg;
    StatementList* stmts;
    Statement* stmt;
    ParamList* params;
    VarType type;
    operation op;
    MyValue value;
    char word[256];
};

%token MAIN MAIN_ARGS PUBLIC VOID STATIC CLASS RETURN WHILE BREAK

%token <type> TYPE
%token <value> INT BOOL
%token <word> ID

%type <expr> EXPR INVOKE_EXPR TERM
%type <value> CONSTANT
%type <method> METHOD_DECLARATION METHOD_HEADER
%type <args> ARGS_DECLARATION
%type <arg> PARAM_DECLARATION
%type <stmts> STATEMENTS
%type <params> PARAMS
%type <stmt> NODE STATEMENT DECLARATION ASSIGNMENT FIELD_DECLARATION
%type <stmt> RETURN_STATEMENT IF_STATEMENT WHILE_STATEMENT BREAK_STATEMENT INVOKE_STATEMENT

%left OR AND GE LE GT LT EQ NEQ NOT
%left '+' '-'
%left '*' '/' '%'
%nonassoc IF 
%nonassoc ELSE

%%
JAVA_PROGRAM :
| CLASS_BODY

CLASS_BODY : PUBLIC CLASS ID '{' FIELD_OR_METHOD_DECLARATION '}'

FIELD_OR_METHOD_DECLARATION : FIELD_DECLARATION { processRule(@$, "FIELD_OR_METHOD_DECLARATION"); mainClass.addFieldDeclaration($1); }
| METHOD_DECLARATION { }

FIELD_DECLARATION : PUBLIC STATIC DECLARATION { }
| FIELD_DECLARATION PUBLIC STATIC DECLARATION { }

METHOD_DECLARATION: METHOD_HEADER '{' NODE '}' { }
| METHOD_DECLARATION METHOD_HEADER '{' NODE '}' { }


METHOD_HEADER : PUBLIC STATIC VOID MAIN '(' MAIN_ARGS ID ')'
{
}
| PUBLIC STATIC TYPE ID '(' ARGS_DECLARATION ')'
{
}
| PUBLIC STATIC VOID ID '(' ARGS_DECLARATION ')'
{
}

ARGS_DECLARATION : PARAM_DECLARATION { }
| ARGS_DECLARATION ',' PARAM_DECLARATION {  }

PARAM_DECLARATION : TYPE ID {}
| {}

NODE : STATEMENTS {}

STATEMENTS : {}
| STATEMENTS STATEMENT { }

STATEMENT : DECLARATION | ASSIGNMENT | RETURN_STATEMENT | IF_STATEMENT | WHILE_STATEMENT | BREAK_STATEMENT | INVOKE_STATEMENT

INVOKE_STATEMENT : INVOKE_EXPR ';' {  }

BREAK_STATEMENT: BREAK ';' { }

WHILE_STATEMENT : WHILE '(' EXPR ')' '{' STATEMENTS '}' { }

IF_STATEMENT : IF '(' EXPR ')' '{' STATEMENTS '}' {}
| IF '(' EXPR ')'  '{' STATEMENTS '}' ELSE '{' STATEMENTS '}' {; }

RETURN_STATEMENT : RETURN EXPR ';' { processRule(@$, "RETURN_STATEMENT"); $$ = new ReturnStatement($2, curMethod); }
| RETURN ';' { }

DECLARATION : TYPE ID ';' { }
| TYPE ID '=' EXPR ';' { }

ASSIGNMENT : ID '=' EXPR ';' {  }

EXPR : TERM {  }
| '(' EXPR ')' { }
| INVOKE_EXPR { }
| EXPR '+' EXPR {  }
| EXPR '-' EXPR {  }
| EXPR '/' EXPR {  }
| EXPR '%' EXPR { }
| EXPR '*' EXPR { }
| EXPR AND EXPR { }
| EXPR OR EXPR { }
| EXPR LT EXPR { }
| EXPR LE EXPR { }
| EXPR GT EXPR { }
| EXPR GE EXPR { }
| EXPR NEQ EXPR { }
| EXPR EQ EXPR { }
| NOT EXPR { }


INVOKE_EXPR: ID '.' ID '(' PARAMS ')' { }

PARAMS : {  }
| EXPR { }
| PARAMS ',' EXPR { }

TERM : ID { }
| CONSTANT { }

CONSTANT : INT | BOOL {  }
%%

void yyerror(const char *s)
{
    fprintf(stderr, "line number %d: ", yylineno);
    fprintf(stderr, "%s\n", s);
}

extern int main(int argc, const char* argv[]);
