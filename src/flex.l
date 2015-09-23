%option noyywrap

%{
#include "tokens_processing.h"
extern "C" {
    void yyerror(char*) {}
    int yyparse(void);
    int yylex(void);
}
%}

IDENT 	[A-Za-z_][A-Za-z0-9_]*
INT 	([1-9]([0-9])*)|0
BOOLEAN	("true"|"false")
SPACE 	[ \t]+
LINE_SEPARATOR [\n]+

%%
if          {    processToken("IF", yytext);	}
else		{ 	 processToken("ELSE", yytext);	}
while		{	 processToken("WHILE", yytext);	}
return		{	 processToken("RETURN", yytext);	}
public:		{	 processToken("PUBLIC", yytext);	}
class		{	 processToken("CLASS", yytext);	}
static		{	 processToken("STATIC", yytext);	}
void		{	 processToken("TYPE_VOID", yytext);	}
main		{	 processToken("MAIN", yytext);	}
int 		{    processToken("TYPE_INT", yytext);	}
boolean		{    processToken("TYPE_BOOL", yytext);	}
String		{	 processToken("TYPE_STRING", yytext);	}
"{"		{	 processToken("{", yytext);	}
"}"		{	 processToken("}", yytext);	}
"("		{	 processToken("(", yytext);	}
")"		{	 processToken(")", yytext);	}
"["		{	 processToken("[", yytext);	}
"]"		{	 processToken("]", yytext);	}
"<"		{	 processToken("<", yytext);	}
"<="		{	 processToken("LESSEQ", yytext);	}
">"		{	 processToken(">", yytext);	}
">="		{	 processToken("MOREEQ", yytext);	}
"=="		{	 processToken("EQ", yytext);	}
"!="		{	 processToken("NONEQ", yytext);	}
"="		{	 processToken("=", yytext);	}
"&&"		{	 processToken("AND", yytext);	}
"||"		{	 processToken("OR", yytext);	}
"+"		{	 processToken("+", yytext);	}
"-"		{	 processToken("-", yytext);	}
"*"		{	 processToken("*", yytext);	}
"/"		{	 processToken("/", yytext);	}
";"		{	 processToken(";", yytext);	}
","		{	 processToken(",", yytext);	}
"!"		{	 processToken("!", yytext);	}
"."		{	 processToken(".", yytext);	}
{BOOLEAN} { processValue("BOOLEAN", yytext); }
{INT} { processValue("INT", yytext); }
{IDENT}	{ processValue("IDENT", yytext); }
{SPACE}	{ processSpace(yytext); }
{LINE_SEPARATOR} {	processNewLine(yytext);	}
. { processErrorToken(yytext); }
%%
