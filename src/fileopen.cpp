//**************************************
// fileopen.cpp
// Author: Jacob Locke
//

#include "fileopen.h"

int fileopen(int argc, char **argv, FILE *&input)
{
    const char *outfile_name;

    // open input
    if (argc > 1)
    {
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            std::cerr << "Unable to open input file " << argv[1] << "\n";
            return -1;
        }
    }

    // open output
    if (argc > 2)
    {
        outfile_name = argv[2];
        FILE *output = fopen(outfile_name, "w");
        if (output == NULL)
        {
            std::cerr << "Unable to open output file " << outfile_name << "\n";
            return -1;
        }
        int output_fd = fileno(output);
        if (dup2(output_fd, 1) != 1)
        {
            std::cerr << "Unable to send output to " << outfile_name << "\n";
            return -2;
        }
    }

    return 0;
}