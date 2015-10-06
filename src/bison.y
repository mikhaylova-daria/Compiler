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
| METHOD_DECLARATION { processRule(@$, "FIELD_OR_METHOD_DECLARATION"); mainClass.addMethod($1); }

FIELD_DECLARATION : PUBLIC STATIC DECLARATION { processRule(@$, "FIELD_DECLARATION"); $$ = $3; }
| FIELD_DECLARATION PUBLIC STATIC DECLARATION { processRule(@$, "FIELD_DECLARATION"); mainClass.addFieldDeclaration($1); $$ = $4; }

METHOD_DECLARATION: METHOD_HEADER '{' NODE '}' { processRule(@$, "METHOD_DECLARATION"); $$ = $1; $$->setBody($3); curMethod = NULL; }
| METHOD_DECLARATION METHOD_HEADER '{' NODE '}' { processRule(@$, "METHOD_DECLARATION"); mainClass.addMethod($1); $$ = $2; $$->setBody($4); curMethod = NULL; }


METHOD_HEADER : PUBLIC STATIC VOID MAIN '(' MAIN_ARGS ID ')'
{   processRule(@$, "METHOD_HEADER");
    $$ = new Method("main", NoType, new ArgumentList());
    mainClass.setMain($$);
    mainArgsId = $7;
    
    MyValue argsValue;
    argsValue.type = Int;
    argsValue.int_value = -1;
    mainClass.addFieldDeclaration(new Declaration($7, Int, new Constant(argsValue)));
}
| PUBLIC STATIC TYPE ID '(' ARGS_DECLARATION ')'
{   processRule(@$, "METHOD_HEADER");
    $$ = new Method($4, $3, $6);
    $$->setNode(new Node(mainClass.getNode()));
    curMethod = $$;
}
| PUBLIC STATIC VOID ID '(' ARGS_DECLARATION ')'
{   processRule(@$, "METHOD_HEADER");
    $$ = new Method($4, NoType, $6);
    $$->setNode(new Node(mainClass.getNode()));
    curMethod = $$;
}

ARGS_DECLARATION : PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); $$ = new ArgumentList(); $$->add($1); }
| ARGS_DECLARATION ',' PARAM_DECLARATION { processRule(@$, "ARGS_DECLARATION"); $$ = $1; $$->add($3); }

PARAM_DECLARATION : TYPE ID { processRule(@$, "PARAM_DECLARATION"); $$ = new Argument($2, $1); }
| { processRule(@$, "PARAM_DECLARATION"); $$ = new Argument(); }

NODE : STATEMENTS { processRule(@$, "NODE"); $$ = new NodeStatement($1); }

STATEMENTS : { processRule(@$, "STATEMENTS"); $$ = new StatementList(); }
| STATEMENTS STATEMENT { processRule(@$, "STATEMENTS"); $$ = $1; $$->add($2); }

STATEMENT : DECLARATION | ASSIGNMENT | RETURN_STATEMENT | IF_STATEMENT | WHILE_STATEMENT | BREAK_STATEMENT | INVOKE_STATEMENT

INVOKE_STATEMENT : INVOKE_EXPR ';' { processRule(@$, "INVOKE_STATEMENT"); $$ = new InvokeStatement($1); }

BREAK_STATEMENT: BREAK ';' { processRule(@$, "BREAK_STATEMENT"); $$ = new BreakStatement(); }

WHILE_STATEMENT : WHILE '(' EXPR ')' '{' STATEMENTS '}' { processRule(@$, "WHILE_STATEMENT"); $$ = new WhileStatement($3, $6); }

IF_STATEMENT : IF '(' EXPR ')' '{' STATEMENTS '}' { processRule(@$, "IF_STATEMENT"); $$ = new IfStatement($3, $6); }
| IF '(' EXPR ')'  '{' STATEMENTS '}' ELSE '{' STATEMENTS '}' { processRule(@$, "IF_STATEMENT"); $$ = new IfStatement($3, $6, $10); }

RETURN_STATEMENT : RETURN EXPR ';' { processRule(@$, "RETURN_STATEMENT"); $$ = new ReturnStatement($2, curMethod); }
| RETURN ';' { processRule(@$, "RETURN_STATEMENT"); $$ = new ReturnStatement(NULL, curMethod); }

DECLARATION : TYPE ID ';' { processRule(@$, "DECLARATION"); $$ = new Declaration($2, $1); }
| TYPE ID '=' EXPR ';' { processRule(@$, "DECLARATION"); $$ = new Declaration($2, $1, $4); }

ASSIGNMENT : ID '=' EXPR ';' { processRule(@$, "ASSIGNMENT"); $$ = new Assignment($1, $3); }

EXPR : TERM { processRule(@$, "EXPR"); $$ = $1; }
| '(' EXPR ')' { processRule(@$, "EXPR"); $$ = $2; }
| INVOKE_EXPR {processRule(@$, "EXPR");  $$ = $1; }
| EXPR '+' EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Add, $1, $3); }
| EXPR '-' EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Sub, $1, $3); }
| EXPR '/' EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Div, $1, $3); }
| EXPR '%' EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Mod, $1, $3); }
| EXPR '*' EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Mul, $1, $3); }
| EXPR AND EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::And, $1, $3); }
| EXPR OR EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Or, $1, $3); }
| EXPR LT EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Less, $1, $3); }
| EXPR LE EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::LessEquals, $1, $3); }
| EXPR GT EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Greater, $1, $3); }
| EXPR GE EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::GreaterEquals, $1, $3); }
| EXPR NEQ EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::NotEquals, $1, $3); }
| EXPR EQ EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Equals, $1, $3); }
| NOT EXPR { processRule(@$, "EXPR"); $$ = new BinExpr(operation::Not, $2, NULL); }

INVOKE_EXPR: ID '.' ID '(' PARAMS ')' { processRule(@$, "INVOKE_EXPR"); $$ = new InvocExpr($5, $3, &library); }
| ID '(' PARAMS ')' { processRule(@$, "INVOKE_EXPR"); $$ = new InvocExpr($3, $1, &mainClass); }

PARAMS : { processRule(@$, "PARAMS"); $$ = new ParamList(); }
| EXPR { processRule(@$, "PARAMS"); $$ = new ParamList(); $$->add($1); }
| PARAMS ',' EXPR { processRule(@$, "PARAMS"); $$ = $1; $$->add($3); }

TERM : ID { processRule(@$, "TERM"); $$ = new VarExpr($1); }
| CONSTANT { processRule(@$, "TERM"); $$ = new Constant($1); }

CONSTANT : INT | BOOL {  processRule(@$, "CONSTANT"); }
%%

void yyerror(const char *s)
{
    fprintf(stderr, "line number %d: ", yylineno);
    fprintf(stderr, "%s\n", s);
}

extern int main(int argc, const char* argv[]);
