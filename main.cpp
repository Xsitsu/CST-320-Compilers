//**************************************
// main.cpp
//
// Main routine for lang compiler.
// This version only runs the lexer
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "cSymbol.h"
#include "cSymbolTable.h"
#include "lex.h"
#include "tokens.h"

#include "fileopen.h"

cSymbolTable g_symbolTable;
long long cSymbol::nextId = 0;
yylval_t yylval;

// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int main(int argc, char **argv)
{
    int result = 0;
    int open_result;
    int token;

    std::cout << "Jacob Locke" << std::endl;

    open_result = fileopen(argc, argv, yyin);
    if (open_result != 0)
    {
        exit(open_result);
    }

    std::cout << "<program>\n";

    token = yylex();
    while (token != 0)
    {
        // if we found an identifier, print it out
        if (token == IDENTIFIER) 
            std::cout << yylval.symbol->ToString() << "\n";
        // else
        //     std::cout << token << ":" << yytext << "\n";
        token = yylex();
    }

    std::cout << "</program>\n";

    return result;
}
