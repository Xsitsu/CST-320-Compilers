#pragma once
//**************************************
// lex.h
//
// Defines global symbols used the the flex generated lexer and 
// bison generated parser.
//
// Author: Phil Howard phil.howard@oit.edu
//

// lexer function generated by flex
int yylex();

extern char *yytext;        // text of the current token
extern int yylineno;        // line number of current token
extern FILE *yyin;          // input file for lexer
