#include "cComputeSize.h"

#include "astnodes.h"

void cComputeSize::VisitAllNodes(cAstNode *node)
{
    node->Visit(this);
    node->VisitAllChildren(this);
}


void cComputeSize::Visit(cAstNode *node)          { node->VisitAllChildren(this); }
void cComputeSize::Visit(cBinaryExprNode *node)   { node->VisitAllChildren(this); }
void cComputeSize::Visit(cIfNode *node)           { node->VisitAllChildren(this); }
void cComputeSize::Visit(cReturnNode *node)       { node->VisitAllChildren(this); }
void cComputeSize::Visit(cWhileNode *node)        { node->VisitAllChildren(this); }
void cComputeSize::Visit(cDeclNode *node)         { node->VisitAllChildren(this); }
void cComputeSize::Visit(cBaseTypeNode *node)     { node->VisitAllChildren(this); }
void cComputeSize::Visit(cArrayDeclNode *node)    { node->VisitAllChildren(this); }
void cComputeSize::Visit(cStructDeclNode *node)   { node->VisitAllChildren(this); }
void cComputeSize::Visit(cFuncDeclNode *node)     { node->VisitAllChildren(this); }
void cComputeSize::Visit(cParamsNode *node)       { node->VisitAllChildren(this); }
void cComputeSize::Visit(cVarExprNode *node)      { node->VisitAllChildren(this); }
void cComputeSize::Visit(cFuncExprNode *node)     { node->VisitAllChildren(this); }
void cComputeSize::Visit(cParamListNode *node)    { node->VisitAllChildren(this); }
void cComputeSize::Visit(cAssignNode *node)       { node->VisitAllChildren(this); }
void cComputeSize::Visit(cExprNode *node)         { node->VisitAllChildren(this); }
void cComputeSize::Visit(cIntExprNode *node)      { node->VisitAllChildren(this); }
void cComputeSize::Visit(cFloatExprNode *node)    { node->VisitAllChildren(this); }
void cComputeSize::Visit(cOpNode *node)           { node->VisitAllChildren(this); }
void cComputeSize::Visit(cPrintNode *node)        { node->VisitAllChildren(this); }
void cComputeSize::Visit(cStmtNode *node)         { node->VisitAllChildren(this); }
void cComputeSize::Visit(cStmtsNode *node)        { node->VisitAllChildren(this); }
void cComputeSize::Visit(cSymbol *node)           { node->VisitAllChildren(this); }








void cComputeSize::Visit(cBlockNode *node)
{
    int offsetOld = this->offset;

    node->VisitAllChildren(this);

    cDeclsNode *decls = node->GetDecls();
    if (decls != nullptr)
    {
        node->SetSize(decls->GetSize());
    }

    this->offset = offsetOld;
}

void cComputeSize::Visit(cDeclsNode *node)
{
    node->VisitAllChildren(this);

    int totalSize = 0;
    for (int i = 0; i < node->NumDecls(); i++)
    {
        cDeclNode *decl = node->GetDecl(i);
        decl->SetOffset(this->m_offset);
        totalSize += decl->GetSize();
        this->m_offset += decl->GetSize();
        while (this->m_offset % 4 != 0) this->m_offset++;
    }

    node->SetSize(totalSize);
}

void cComputeSize::Visit(cVarDeclNode *node)
{
    node->VisitAllChildren(this);

    cDeclNode *type = node->GetType();
    if (type != nullptr)
    {
        node->SetSize(type->GetSize());
    }
}

void cComputeSize::Visit(cProgramNode *node)
{
    node->VisitAllChildren(this);

    cBlockNode* block = node->GetBlock();
    int size = block->GetSize();
    if (size % 4 != 0) size = ((size / 4) * 4) + 4;
    node->SetSize(size);
}
