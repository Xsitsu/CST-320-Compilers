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
    int offsetOld = this->m_offset;
    int maxSizeOld = this->m_maxSize;
    int sizeOld = this->m_size;

    this->m_maxSize = 0;
    this->m_size = 0;

    node->VisitAllChildren(this);

    this->m_maxSize += this->m_size;
    node->SetSize(this->m_maxSize);

    if (maxSizeOld > this->m_maxSize)
    {
        this->m_maxSize = maxSizeOld;
    }

    this->m_offset = offsetOld;
    this->m_size = sizeOld;
}

void cComputeSize::Visit(cDeclsNode *node)
{
    node->VisitAllChildren(this);

    for (int i = 0; i < node->NumDecls(); i++)
    {
        cDeclNode *decl = node->GetDecl(i);
        if (!decl->IsStruct() && !decl->IsFunc())
        {
            int typeSize = decl->GetSize();
            if (typeSize > 1)
            {
                while (this->m_offset % 4 != 0)
                {
                    this->m_offset++;
                    this->m_size++;
                }
            }

            decl->SetOffset(this->m_offset);
            this->m_size += typeSize;
            this->m_offset += typeSize;
        }
    }

    node->SetSize(this->m_size);
}

void cComputeSize::Visit(cStructDeclNode *node)
{
    int offsetOld = this->m_offset;
    int maxSizeOld = this->m_maxSize;
    int sizeOld = this->m_size;

    this->m_offset = 0;
    this->m_maxSize = 0;
    this->m_size = 0;

    node->VisitAllChildren(this);

    int size = this->m_size + this->m_maxSize;
    node->SetSize(size);

    this->m_offset = offsetOld;
    this->m_maxSize = maxSizeOld;
    this->m_size = sizeOld;
}

void cComputeSize::Visit(cFuncDeclNode *node)
{
    int offsetOld = this->m_offset;
    int maxSizeOld = this->m_maxSize;
    int sizeOld = this->m_size;

    this->m_offset = 0;
    this->m_maxSize = 0;
    this->m_size = 0;

    node->VisitAllChildren(this);

    int size = this->m_size + this->m_maxSize;
    while (size % 4 != 0) size++;
    node->SetSize(size);

    this->m_offset = offsetOld;
    this->m_maxSize = maxSizeOld;
    this->m_size = sizeOld;
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
