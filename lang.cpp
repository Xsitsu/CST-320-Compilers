//**************************************
// lang.cpp
//
// Main routine for lang compiler.
//
// Author: Jacob Locke
//
// Date: Jan. 14, 2021
//


#include <iostream>

#include "lex.h"
#include "test_parse_tree.h"

// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int main(int argc, char **argv)
{
    int result = 0;

    std::cout << "Jacob Locke" << std::endl;

    g_symbolTable = new cSymbolTable();
    result = test_parse_tree(argc, argv);

    return result;
}
