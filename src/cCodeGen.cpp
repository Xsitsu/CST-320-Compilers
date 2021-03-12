#include "cCodeGen.h"

#include "astnodes.h"
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

void cCodeGen::Visit(cBlockNode *node)
{
    EmitString("ADJSP");
    EmitInt(node->GetSize());
    EmitString("\n");

    node->VisitAllChildren(this);

    EmitString("ADJSP");
    EmitInt(-node->GetSize());
    EmitString("\n");
}

void cCodeGen::Visit(cPrintNode* node)
{
    node->VisitAllChildren(this);

    EmitString("CALL @print\n");
}

void Visit(cIntExprNode* node)
{
    EmitString("PUSH");
    EmitInt(node->GetValue());
    EmitString("\n");
}
