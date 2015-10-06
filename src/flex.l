%option noyywrap

%{
    #include "JavaHelp.h"
    #include "Declaration.h"
    #include "tokens.h"
    #include <string.h>
    void yyerror(const char*);
    //extern char* yytext;
    //extern Location yylloc;
    int yy_line = 0;
    int yy_column = 0;
    //Location currLocation(0,0,0,0);
    void updateLocation() {
        //currLocation.update(yy_line, yy_column);
        //yylloc.update(yy_line, yy_column);
        yylloc.first_line = yylloc.last_line;
        yylloc.first_column = yylloc.last_column;
        yylloc.last_line = yy_line;
        yylloc.last_column = yy_column;
    }
%}

%option yylineno

%%
[/][/].*\n  { ++yy_line; yy_column = 0; updateLocation(); } // comment
[ \t]+  { yy_column += strlen(yytext); updateLocation();}
[\n]+ { yy_line += strlen(yytext); yy_column = 0; updateLocation();}
[0-9]+ {
    yy_column += strlen(yytext);
    yylval.value.type = Int;
    yylval.value.int_value = atoi(yytext);
    updateLocation();
    return INT;
}

"true" {
    yy_column += strlen(yytext);
    yylval.value.type = Bool;
    yylval.value.bool_value = true;
    updateLocation();
    return BOOL;
}
"false" {
    yy_column += strlen(yytext);
    yylval.value.type = Bool;
    yylval.value.bool_value = false;
    updateLocation();
    return BOOL;
}

"int" {
    yy_column += strlen(yytext);
    yylval.type = Int;
    updateLocation();
    return TYPE;
}
"boolean" {
    yy_column += strlen(yytext);
    yylval.type = Bool;
    updateLocation();
    return TYPE;
}

"public"    { yy_column += strlen(yytext); updateLocation(); return PUBLIC; }
"void"      { yy_column += strlen(yytext); updateLocation(); return VOID; }
"class"     { yy_column += strlen(yytext); updateLocation(); return CLASS; }
"static"    { yy_column += strlen(yytext); updateLocation(); return STATIC;}
"return"    { yy_column += strlen(yytext); updateLocation(); return RETURN; }
"if"        { yy_column += strlen(yytext); updateLocation(); return IF; }
"else"      { yy_column += strlen(yytext); updateLocation(); return ELSE; }
"while"     { yy_column += strlen(yytext); updateLocation(); return WHILE; }
"break"     { yy_column += strlen(yytext); updateLocation(); return BREAK; }
"main"      { yy_column += strlen(yytext); updateLocation(); return MAIN; }
"String[]"  { yy_column += strlen(yytext); updateLocation(); return MAIN_ARGS; }
"&&"        { yy_column += strlen(yytext); updateLocation(); return AND; }
"||"        { yy_column += strlen(yytext); updateLocation(); return OR; }
"!"         { yy_column += strlen(yytext); updateLocation(); return NOT; }
"<="        { yy_column += strlen(yytext); updateLocation(); return LE; }
">="        { yy_column += strlen(yytext); updateLocation(); return GE; }
"=="        { yy_column += strlen(yytext); updateLocation(); return EQ; }
"!="        { yy_column += strlen(yytext); updateLocation(); return NEQ; }
"<"         { yy_column += strlen(yytext); updateLocation(); return LT; }
">"         { yy_column += strlen(yytext); updateLocation(); return GT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yy_column += strlen(yytext);
    strcpy(yylval.word, yytext);
    updateLocation();
    return ID;
}

[-+*/()_{}=;,<>.{}%] { ++yy_column; updateLocation(); return *yytext; }
.        { yyerror("Unknown symbol\n"); }
%%
