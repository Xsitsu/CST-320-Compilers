//**************************************
// test_scanner.cpp
//
// Test routine for the scanner.
//
// Author: Jacob Locke
//
// Date: Jan. 14, 2021
//

#include <iostream>

#include "cSymbol.h"
//#include "cSymbolTable.h"
#include "lex.h"
#include "langparse.h"

#include "fileopen.h"

//cSymbolTable g_symbolTable;
//long long cSymbol::nextId = 0;
//yylval_t yylval;

// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int test_scanner(int argc, char **argv)
{
    int result = 0;
    int open_result;
    int token;
    
    open_result = fileopen(argc, argv, yyin);
    if (open_result != 0)
    {
        exit(open_result);
    }

    token = yylex();
    while (token != 0)
    {
        std::cout << token << ":" << yytext << "\n";
        token = yylex();
    }

    return result;
}
