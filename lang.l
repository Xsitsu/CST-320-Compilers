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
letters						[a-z]
%%

 /*Punctuation*/
[(){}\[\];,\.+\-*\/%=><]		{
									DO_RETURN(yytext[0]);
								}
 /*Operators*/
"!="							DO_RETURN(NOT_EQUALS);
"=="							DO_RETURN(EQUALS);
"&&"							DO_RETURN(AND);
"||"							DO_RETURN(OR);
">="							DO_RETURN(GE);
"<="							DO_RETURN(LE);



 /* token definitions. I gave "program" as an example*/
"program"						DO_RETURN(PROGRAM);

%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
	printf("Scanned '%s': %d\n", yytext, val);
	return val;
}
