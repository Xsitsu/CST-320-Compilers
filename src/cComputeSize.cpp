#include "cComputeSize.h"

#include "astnodes.h"

void cComputeSize::Visit(cBlockNode *node)
{
    node->VisitAllChildren(this);
    cDeclsNode *decls = node->GetDecls();
    if (decls != nullptr)
    {
        node->SetSize(node->GetDecls()->GetSize());
    }
}

void cComputeSize::Visit(cDeclsNode *node)
{
    node->VisitAllChildren(this);

    int totalSize = 0;
    for (int i = 0; i < node->NumDecls(); i++)
    {
        cDeclNode *decl = node->GetDecl(i);
        decl->SetOffset(totalSize);
        totalSize += decl->GetSize();
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
        this->VisitAllChildren(this);

        cBlockNode* block = node->GetBlock();
        int size = block->GetSize();
        if (size % 4 != 0) size = (size / 4) + 4;
        block->SetSize(size);
}
