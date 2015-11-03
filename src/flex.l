%option noyywrap

%{
    //#include "JavaHelp.h"
    //#include "Declaration.h"
    #include "tree/MinijavaTree.h"
    #include "tree/TreeBuildHelp.h"
    #include "tokens.h"
    #include <string.h>
    void yyerror(const char*);
    int yy_line = 1;
    int yy_column = 1;
    //Location currLocation(0,0,0,0);
    void updateLocation() {
        //currLocation.update(yy_line, yy_column);
        //yylloc.update(yy_line, yy_column);
        yylloc.first_line = yylloc.last_line >  1 ? yylloc.last_line : 1;
        yylloc.first_column = yylloc.last_column > 1 ? yylloc.last_column : 1;
        yylloc.last_line = yy_line;
        yylloc.last_column = yy_column;
    }
%}

%option yylineno

%%
[/][/].*\n  { ++yy_line; yy_column = 1; updateLocation(); } // comment
[ \t]+  { yy_column += strlen(yytext); updateLocation();}
[\n]+ { yy_line += strlen(yytext); yy_column = 1; updateLocation();}
[0-9]+ {
    yy_column += strlen(yytext);
    updateLocation();
    return INT_VALUE;
}

"true" {
    yy_column += strlen(yytext);
    updateLocation();
    return BOOL_VALUE;
}
"false" {
    yy_column += strlen(yytext);
    updateLocation();
    return BOOL_VALUE;
}

"int" {
    yy_column += strlen(yytext);
    updateLocation();
    return INT;
}
"boolean" {
    yy_column += strlen(yytext);
    updateLocation();
    return BOOL;
}

"System.out.println"    { yy_column += strlen(yytext); updateLocation(); return PRINT; }
"this"      { yy_column += strlen(yytext); updateLocation(); return THIS; }
"length"    { yy_column += strlen(yytext); updateLocation(); return LENGTH; }
"new"       { yy_column += strlen(yytext); updateLocation(); return NEW; }
"extends"   { yy_column += strlen(yytext); updateLocation(); return EXTENDS; }
"public"    { yy_column += strlen(yytext); updateLocation(); return PUBLIC; }
"void"      { yy_column += strlen(yytext); updateLocation(); return VOID; }
"class"     { yy_column += strlen(yytext); updateLocation(); return CLASS; }
"static"    { yy_column += strlen(yytext); updateLocation(); return STATIC;}
"return"    { yy_column += strlen(yytext); updateLocation(); return RETURN; }
"if"        { yy_column += strlen(yytext); updateLocation(); return IF; }
"else"      { yy_column += strlen(yytext); updateLocation(); return ELSE; }
"while"     { yy_column += strlen(yytext); updateLocation(); return WHILE; }
"main"      { yy_column += strlen(yytext); updateLocation(); return MAIN; }
"String[]"  { yy_column += strlen(yytext); updateLocation(); return MAIN_ARGS; }
"&&"        { yy_column += strlen(yytext); updateLocation(); return AND; }
"!"         { yy_column += strlen(yytext); updateLocation(); return NOT; }
"=="        { yy_column += strlen(yytext); updateLocation(); return EQ; }
"<"         { yy_column += strlen(yytext); updateLocation(); return '<'; }
"["         { yy_column += strlen(yytext); updateLocation(); return '['; }
"]"         { yy_column += strlen(yytext); updateLocation(); return ']'; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yy_column += strlen(yytext);
    updateLocation();
    return _ID;
}

[-+*/()_{}=;,<>.{}%] { ++yy_column; updateLocation(); return *yytext; }
.        { yyerror("Unknown symbol\n"); }
%%
