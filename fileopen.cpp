#include "fileopen.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int fileopen(int argc, char **argv, FILE &*input)
{
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
        FILE *output = fopen(argv[2], "w");
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