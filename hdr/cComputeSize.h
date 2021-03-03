#pragma once

#include "cVisitor.h"

class cComputeSize : cVisitor
{
    public:
        cComputeSize() {}

        virtual void Visit(cBlockNode *node);
        //virtual void Visit(cBinaryExprNode *node);
        //virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        //virtual void Visit(cBaseTypeNode *node);
        virtual void Visit(cVarDeclNode *node);
        //virtual void Visit(cArrayDeclNode *node);
        //virtual void Visit(cStructDeclNode *node);
        //virtual void Visit(cFuncDeclNode *node);
        //virtual void Visit(cParamsNode *node);
        //virtual void Visit(cVarExprNode *node);
        //virtual void Visit(cFuncExprNode *node);
        //virtual void Visit(cParamListNode *node);
        //virtual void Visit(cExprNode *node);
        //virtual void Visit(cIntExprNode *node);
        //virtual void Visit(cFloatExprNode *node);
        virtual void Visit(cProgramNode *node);
}