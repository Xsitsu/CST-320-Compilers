//**************************************
// test_parse_tree.cpp
//
// Test routine for the parse tree.
//
// Author: Jacob Locke
//
// Date: Jan. 30, 2021
//

#include "test_code.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "lex.h"
#include "astnodes.h"
#include "langparse.h"

#include "cComputeSize.h"
#include "cCodeGen.h"

// **************************************************
// argv[1] is the input file
// argv[2] if present, is the output file
int test_parse_tree(int argc, char **argv)
{
    int result = 0;
    std::string outfile_name;

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == nullptr)
        {
            std::cerr << "ERROR: Unable to open file " << argv[1] << "\n";
            exit(-1);
        }
    }

    if (argc > 2)
    {
        outfile_name = argv[2];
    } else {
        outfile_name = "langout";
    }

    result = yyparse();
    if (yyast_root != nullptr)
    {
        if (result == 0)
        {
            cComputeSize sizer;
            sizer.VisitAllNodes(yyast_root);
           
           {
               cCodeGen coder(outfile_name + ".sl");
               coder.VisitAllNodes(yyast_root);
           }

           std::string cmd = "slasm" + outfile_name + ".sl io320.sl";
           system(cmd.c_str());
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
