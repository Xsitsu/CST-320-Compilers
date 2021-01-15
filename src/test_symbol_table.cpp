//**************************************
// test_symbol_table.cpp
//
// Test routine for the symbol table.
//
// Author: Jacob Locke
//
// Date: Jan. 14, 2021
//

#include <iostream>

#include "cSymbol.h"
//#include "cSymbolTable.h"
#include "lex.h"
#include "tokens.h"

#include "fileopen.h"

//cSymbolTable g_symbolTable;
long long cSymbol::nextId = 0;
yylval_t yylval;

// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int test_symbol_table(int argc, char **argv)
{
    int result = 0;
    int open_result;
    int token;

    open_result = fileopen(argc, argv, yyin);
    if (open_result != 0)
    {
        exit(open_result);
    }

    std::cout << "<program>\n";

    token = yylex();
    while (token != 0)
    {
        if (token == IDENTIFIER)
            std::cout << yylval.symbol->ToString() << "\n";
        token = yylex();
    }

    std::cout << "</program>\n";

    return result;
}
