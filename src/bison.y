%{
    #include <cstdio>
    #include <string>
    #include <iostream>

    using namespace std;
    #define YYSTYPE string
    #define YYERROR_VERBOSE 1
    #define DEBUG

    int  wrapRet = 1;

    extern "C" {
        int yywrap( void ) {
            return wrapRet;
        }
        int yylex(void);
    }
    void yyerror(const char *str) {
        #ifdef DEBUG
          //cout << "Python Parser: " << str << endl;
        #endif
    }
    int main();
%}
%token CLASS DEFINED COLON DOT LBRACE RBRACE
%token ID OTHER DEF COMMA STAR MESSAGE
%start input
%%
input: /* empty */
     | input class_def
     | input func_def
     | input error
;
/* CLASS */
class_def: CLASS classname inheritance COLON suite
    {
        #ifdef DEBUG
            cout << " >> CLASS: "
                 << $2            << "("
                 << $3            << ")"
                 << endl;
        #endif
    }
;
classname: ID
           {
               $$ = $1;
           }
;
inheritance: /* empty */
             {
                 $$ = "";
             }
           | LBRACE class_args_list RBRACE
             {
                 $$ = $2;
             }
;
class_args_list: /* empty */
                 {
                     $$ = "";
                 }
               | class_arg
                 {
                     $$ = $1;
                 }
;
class_arg: ID
         | class_arg COMMA
           {
               $$ += $2;
           }
         | class_arg ID
           {
               $$ += $2;
           }
         | class_arg DOT
           {
               $$ += $2;
           }
;
/* end of CLASS */
/* FUNCTION */
func_def: DEF funcname LBRACE func_args_list RBRACE COLON suite
          {
              #ifdef DEBUG
                  cout << " >> FUNC:  "
                       << $2            << "("
                       << $4            << ")"
                       << endl;
              #endif
          }
;
funcname: ID
          {
              $$ = $1;
          }
;
func_args_list: /* empty */
                {
                    $$ = "";
                }
              | func_arg
                {
                    $$ = $1;
                }
;
func_arg: dotted_name
        | star_arg
        | func_arg OTHER
          {
              $$ += $2;
          }
        | func_arg COMMA
          {
              $$ += $2;
          }
        | func_arg dotted_name
          {
              $$ += $2;
          }
        | func_arg star_arg
          {
              $$ += $2;
          }
        | func_arg MESSAGE
          {
              $$ += $2;
          }
;
star_arg: STAR ID
          {
              $$ = $1 + $2;
          }
        | STAR STAR ID
          {
              $$ = $1 + $2 + $3;
          }
;
/* end of FUNCTION */
dotted_name: ID
           | dotted_name DOT ID
             {
                 $$ += $2 + $3;
             }
;
suite:
;
%%
extern int main();