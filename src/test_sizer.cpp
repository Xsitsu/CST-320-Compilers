//**************************************
// test_parse_tree.cpp
//
// Test routine for the size and offset visitor.
//
// Author: Jacob Locke
//
// Date: Jan. 30, 2021
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include "cSymbolTable.h"
#include "lex.h"
#include "astnodes.h"
#include "langparse.h"

#include "fileopen.h"

#include "cComputeSize.h"


// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int test_sizer(int argc, char **argv)
{
    int result = 0;
    int open_result;

    open_result = fileopen(argc, argv, yyin);
    if (open_result != 0)
    {
        exit(open_result);
    }   

    result = yyparse();
    if (yyast_root != nullptr)
    {
        if (result == 0)
        {
            cComputeSize sizer;
            sizer.VisitAllNodes(yyast_root);
            std::cout << yyast_root->ToString() << std::endl;
        }
        else
        {
            std::cout << yynerrs << " Errors in compile\n";
        }
    }

    if (result == 0 && yylex() != 0)
    {
        std::cout << "Junk at end of program\n";
    }

    return result;
}
