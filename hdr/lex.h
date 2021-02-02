#pragma once
//**************************************
// lex.h
//
// Defines global symbols used the the flex generated lexer and 
// bison generated parser.
//
// Author: Phil Howard phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSymbolTable.h"

int yyparse();                          // parsing function
int yylex();                            // scanning function
extern char *yytext;                    // text of current token
extern int yylineno;                    // line number of input file
extern int yynerrs;                     // Num of compile errors
extern FILE *yyin;                      // FILE pointer for input
extern cAstNode *yyast_root;            // root of AST

extern cSymbolTable *g_symbolTable;

cSymbol *Insert(const char *text);
void IncreaseScope();
void DecreaseScope();