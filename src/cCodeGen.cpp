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

void cCodeGen::Visit(cProgramNode *node)
{
    EmitString(".function main\n");
    EmitString("main:\n");
    node->VisitAllChildren(this);
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

void cCodeGen::Visit(cIntExprNode* node)
{
    EmitString("PUSH");
    EmitInt(node->GetValue());
    EmitString("\n");
}

void cCodeGen::Visit(cBinaryExprNode *node)
{
    node->GetLeft()->Visit(this);
    node->GetRight()->Visit(this);
    node->GetOp()->Visit(this);
}

void cCodeGen::Visit(cOpNode *node)
{
    switch(node->GetOp())
    {
    case '+':
        EmitString("PLUS\n");
        break;
    case '-':
        EmitString("MINUS\n");
        break;
    case '*':
        EmitString("TIMES\n");
        break;
    case '/':
        EmitString("DIVIDE\n");
        break;
    case '%':
        EmitString("MOD\n");
        break;
    }
}

void cCodeGen::Visit(cAssignNode *node)
{
    node->GetExpr()->Visit(this);

    EmitString("POPVAR");
    EmitInt(node->GetLVal()->GetOffset());
    EmitString("\n");
}

void cCodeGen::Visit(cVarExprNode *node)
{
    EmitString("PUSHVAR");
    EmitInt(node->GetOffset());
    EmitString("\n");
}

void cCodeGen::Visit(cIfNode *node)
{
    std::string label = GenerateLabel();
    node->GetCondition()->Visit(this);
    EmitString("JUMPE @" + label + "\n");
    node->GetIfStmts()->Visit(this);

    cStmtsNode *elseStmts = node->GetElseStmts();
    if (elseStmts != nullptr)
    {
        EmitString("JUMP @" + label + "_ELSE\n");
        EmitString(label + ":");
        elseStmts->Visit(this);
        EmitString(label + "_ELSE:\n");
    }
    else
    {
        EmitString(label + ":");
    }
}