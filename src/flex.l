%option noyywrap

%{
    #include "JavaHelp.h"
    #include "Declaration.h"
    #include "tokens.h"
    void yyerror(const char*);
%}

%option yylineno

%%
[/][/].*\n      ; // comment
[ \t\n] ;

[0-9]+ {
    yylval.value.type = Int;
    yylval.value.int_value = atoi(yytext);
    return INT;
}

"true" {
    yylval.value.type = Bool;
    yylval.value.bool_value = true;
    return BOOL;
}
"false" {
    yylval.value.type = Bool;
    yylval.value.bool_value = false;
    return BOOL;
}

"int" {
    yylval.type = Int;
    return TYPE;
}
"boolean" {
    yylval.type = Bool;
    return TYPE;
}

"public"    { return PUBLIC; }
"void"      { return VOID; }
"class"     { return CLASS; }
"static"    { return STATIC;}
"return"    { return RETURN; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"break"     { return BREAK; }
"main"      { return MAIN; }
"String[]" { return MAIN_ARGS; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }
"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"!="        { return NEQ; }
"<"         { return LT; }
">"         { return GT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    strcpy(yylval.word, yytext);
    return ID;
}

[-+*/()_{}=;,<>.{}%] { return *yytext; }
.        { yyerror("Unknown symbol\n"); }
%%
