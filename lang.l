%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: Jacob Locke
//

#include "lex.h"
#include "tokens.h"

// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
#define DO_RETURN(a) { return (a); }
//#define DO_RETURN(a) { return Return(a); }

int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
    /* NOTE: You do not need to use definitions */
letters                     [a-z]
whitespace                  [\t\n\r ]
identifier                  [a-zA-Z_][a-zA-Z0-9_]*

%%
{whitespace}*                   ; /* ignore whitespace */
"//".*"\n"                      ; /* ignore C++ style comments */


 /*Punctuation*/
[()\[\];,\.+\-*\/%=><]          {
                                    DO_RETURN(yytext[0]);
                                }

"{"                             {
/*                                    IncreaseScope();*/
                                    DO_RETURN(yytext[0]);
                                }
"}"                             {
/*                                    DecreaseScope();*/
                                    DO_RETURN(yytext[0]);
                                }


 /*Operators*/
"!="                            DO_RETURN(NOT_EQUALS);
"=="                            DO_RETURN(EQUALS);
"&&"                            DO_RETURN(AND);
"||"                            DO_RETURN(OR);
">="                            DO_RETURN(GE);
"<="                            DO_RETURN(LE);

 /*Keywords*/
"program"                       DO_RETURN(PROGRAM);
"if"                            DO_RETURN(IF);
"else"                          DO_RETURN(ELSE);
"endif"                         DO_RETURN(ENDIF);
"while"                         DO_RETURN(WHILE);
"print"                         DO_RETURN(PRINT);
"int"                           DO_RETURN(INT);
"float"                         DO_RETURN(FLOAT);
"char"                          DO_RETURN(CHAR);
"struct"                        DO_RETURN(STRUCT);
"array"                         DO_RETURN(ARRAY);
"return"                        DO_RETURN(RETURN);

 /*Others*/
 {identifier}                   {
/*                                    yylval.symbol = Insert(yytext);*/
                                    DO_RETURN(IDENTIFIER);
                                }

 [0-9]+                         DO_RETURN(INT_VAL);
 [0-9]+\.[0-9]+                 DO_RETURN(FLOAT_VAL);

 /*Junk*/
 .                              DO_RETURN(JUNK_TOKEN);
%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
