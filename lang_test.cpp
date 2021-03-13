//**************************************
// lang_test.cpp
//
// Test program for lang compiler.
// Takes a lang file as input and outputs
// to a file depending on the output
// mode.
//
// Author: Jacob Locke
//
// Date: Jan. 14, 2021
//

#include <stdlib.h>
#include <iostream>

#include "lex.h"
#include "test_scanner.h"
#include "test_symbol_table.h"
#include "test_parse_tree.h"
#include "test_sizer.h"
#include "test_code.h"

#define TEST_MODE_NONE 0
#define TEST_MODE_SCANNER 1
#define TEST_MODE_SYMBOL_TABLE 2
#define TEST_MODE_PARSE_TREE 3
#define TEST_MODE_SEMANTIC_ERRORS 4
#define TEST_MODE_SIZER 5
#define TEST_MODE_CODE 6

// **************************************************
// argv[1] is the test mode
// argv[2] is the input file
// argv[3] if present, is the output file
int main(int argc, char **argv)
{
    int result = 0;
    int test_mode = TEST_MODE_NONE;

    g_symbolTable = new cSymbolTable();

    if (argc > 1)
    {
        test_mode = atoi(argv[1]);
    }

    if (test_mode == TEST_MODE_SCANNER)
    {
        test_scanner(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_SYMBOL_TABLE)
    {
        test_symbol_table(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_PARSE_TREE)
    {
        test_parse_tree(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_SEMANTIC_ERRORS)
    {
        test_parse_tree(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_SIZER)
    {
        test_sizer(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_CODE)
    {
        test_code(argc - 1, argv + 1);
    }
    else if (test_mode == TEST_MODE_NONE)
    {
        std::cout << "Test mode was not provided." << std::endl;
    }
    else
    {
        std::cerr << "Invalid test mode got: " << test_mode << std::endl;
        exit(-1);
    }

    return result;
}
