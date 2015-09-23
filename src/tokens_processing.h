#ifndef MINIJAVACOMPILER_TOKENS_PREPROCESSING_H
#define MINIJAVACOMPILER_TOKENS_PREPROCESSING_H

void processToken(const char* token, const char* yytext);
void processValue(const char* token, const char* yytext);
void processNewLine(const char* yytext);
void processSpace(const char* yytext);
void processErrorToken(const char* yytext);

#endif //MINIJAVACOMPILER_TOKENS_PREPROCESSING_H
