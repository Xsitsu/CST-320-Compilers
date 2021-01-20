#pragma once
//**************************************
// fileopen.h
// Author: Jacob Locke
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

int fileopen(int argc, char **argv, FILE *&input);
