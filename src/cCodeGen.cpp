#include "cCodeGen.h"

#include "emit.h"

cCodeGen::cCodeGen(const std::string input_file)
{
    InitOutput(input_file);
}

cCodeGen::~cCodeGen()
{
    FinalizeOutput();
}

void cCodeGen::VisitAllNodes(cAstNode *node)
{
    node->Visit(this);
}
