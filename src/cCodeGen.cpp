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
    std::string op = node->GetOpAsString();
    if (op == "+")
    {
        EmitString("PLUS\n");
    }
    else if (op == "-")
    {
        EmitString("MINUS\n");
    }
    else if (op == "*")
    {
        EmitString("TIMES\n");
    }
    else if (op == "/")
    {
        EmitString("DIVIDE\n");
    }
    else if (op == "%")
    {
        EmitString("MOD\n");
    }
    else if (op == "!=")
    {
        EmitString("NE\n");
    }
    else if (op == "==")
    {
        EmitString("EQ\n");
    }
    else if (op == "||")
    {
        EmitString("OR\n");
    }
    else if (op == "AND")
    {
        EmitString("AND\n");
    }
    else if (op == "GE")
    {
        EmitString("GE\n");
    }
    else if (op == "GT")
    {
        EmitString("GT\n");
    }
    else if (op == "LE")
    {
        EmitString("LE\n");
    }
    else if (op == "LT")
    {
        EmitString("LT\n");
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
        EmitString(label + ":\n");
        elseStmts->Visit(this);
        EmitString(label + "_ELSE:\n");
    }
    else
    {
        EmitString(label + ":");
    }
}

void cCodeGen::Visit(cWhileNode *node)
{
    std::string label = GenerateLabel();
    EmitString(label + "_WHILE_START:\n");
    node->GetExpr()->Visit(this);
    EmitString("JUMP @" + label + "_WHILE_END\n");
    node->GetStmt()->Visit(this);
    EmitString("JUMP @" + label + "_WHILE_START\n");
    EmitString(label + "_WHILE_END:\n");
}