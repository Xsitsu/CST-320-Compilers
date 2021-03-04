#pragma once

#include "cVisitor.h"

class cComputeSize : cVisitor
{
    public:
        cComputeSize() : m_offset(0), m_size(0), m_maxSize(0) {}

        virtual void VisitAllNodes(cAstNode *node);

        virtual void Visit(cAstNode *node);
        virtual void Visit(cBlockNode *node);
        virtual void Visit(cBinaryExprNode *node);
        virtual void Visit(cIfNode *node);
        virtual void Visit(cReturnNode *node);
        virtual void Visit(cWhileNode *node);
        virtual void Visit(cDeclNode *node);
        virtual void Visit(cDeclsNode *node);
        virtual void Visit(cBaseTypeNode *node);
        virtual void Visit(cVarDeclNode *node);
        virtual void Visit(cArrayDeclNode *node);
        virtual void Visit(cStructDeclNode *node);
        virtual void Visit(cFuncDeclNode *node);
        virtual void Visit(cParamsNode *node);
        virtual void Visit(cVarExprNode *node);
        virtual void Visit(cFuncExprNode *node);
        virtual void Visit(cParamListNode *node);
        virtual void Visit(cAssignNode *node);
        virtual void Visit(cExprNode *node);
        virtual void Visit(cIntExprNode *node);
        virtual void Visit(cFloatExprNode *node);
        virtual void Visit(cOpNode *node);
        virtual void Visit(cPrintNode *node);
        virtual void Visit(cProgramNode *node);
        virtual void Visit(cStmtNode *node);
        virtual void Visit(cStmtsNode *node);
        virtual void Visit(cSymbol *node);

    protected:
        int m_offset;
        int m_size;
        int m_maxSize;
};
