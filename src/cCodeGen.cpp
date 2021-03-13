#include "cCodeGen.h"

#include "astnodes.h"
#include "emit.h"

void DoStackAdjust(int size)
{
    if (size != 0)
    {
        EmitString("ADJSP");
        EmitInt(size);
        EmitString("\n");
    }
}

void cCodeGen::OutputcFuncDeclNode(cFuncDeclNode *node)
{
    std::string funcName = node->GetName()->GetName();
    EmitString("\n.function " + funcName + "\n");
    EmitString(funcName + ":\n");

    int size = node->GetSize();
    DoStackAdjust(size);

    cDeclsNode *decls = node->GetDecls();
    if (decls != nullptr)
    {
        decls->VisitAllChildren(this);
    }

    cStmtsNode *stmts = node->GetStmts();
    if (stmts != nullptr)
    {
        stmts->VisitAllChildren(this);
    }

    EmitString("RETURNV\n");
}

cCodeGen::cCodeGen(const std::string input_file) : func_decls()
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
    EmitString("RETURN\n");

    // Must iterate by index because some weird people
    // may choose to declare functions inside of functions
    // which would modify func_decls and invalidate any
    // iterators.
    for (int i = 0; i < (int)this->func_decls.size(); i++)
    {
        this->OutputcFuncDeclNode(this->func_decls[i]);
    }
}

void cCodeGen::Visit(cBlockNode *node)
{
    int size = node->GetSize();
    DoStackAdjust(size);
    node->VisitAllChildren(this);
    DoStackAdjust(-size);
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

    cVarExprNode *lval = node->GetLVal();
    if (lval->GetType()->IsNumber())
    {
        EmitString("POPVAR");
        EmitInt(lval->GetOffset());
        EmitString("\n");
    }
    else if (lval->GetType()->IsStruct())
    {
        cDeclNode *decl = lval->GetLastDecl();
        cStructDeclNode *struct_decl = static_cast<cStructDeclNode*>(decl->GetType());
        cDeclsNode *decls = struct_decl->GetDecls();
        for (int i = decls->NumDecls(); i > 0; i--)
        {
            EmitString("POPVAR");
            EmitInt(decl->GetOffset() + decls->GetDecl(i - 1)->GetOffset());
            EmitString("\n");
        }
    }
}

void cCodeGen::Visit(cVarExprNode *node)
{
    if (node->GetType()->IsNumber())
    {
        EmitString("PUSHVAR");
        EmitInt(node->GetOffset());
        EmitString("\n");
    }
    else if (node->GetType()->IsStruct())
    {
        cDeclNode *decl = node->GetLastDecl();
        cStructDeclNode *struct_decl = static_cast<cStructDeclNode*>(decl->GetType());
        cDeclsNode *decls = struct_decl->GetDecls();
        for (int i = 0; i < decls->NumDecls(); i++)
        {
            EmitString("PUSHVAR");
            EmitInt(decl->GetOffset() + decls->GetDecl(i)->GetOffset());
            EmitString("\n");
        }
    }
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
    EmitString("JUMPE @" + label + "_WHILE_END\n");
    node->GetStmt()->Visit(this);
    EmitString("JUMP @" + label + "_WHILE_START\n");
    EmitString(label + "_WHILE_END:\n");
}

void cCodeGen::Visit(cFuncDeclNode *node)
{
    this->func_decls.push_back(node);
}

void cCodeGen::Visit(cFuncExprNode *node)
{
    node->VisitAllChildren(this);
    EmitString("CALL @" + node->GetName()->GetName() + "\n");
}

void cCodeGen::Visit(cParamListNode *node)
{
    for (int i = node->NumParams(); i > 0; i--)
    {
        node->GetParam(i - 1)->Visit(this);
    }
}