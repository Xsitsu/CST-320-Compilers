#pragma once

#include <string>
#include <vector>

#include "cVisitor.h"

class cCodeGen : public cVisitor
{
    protected:
        std::vector<cFuncDeclNode*> func_decls;
    public:
        cCodeGen(const std::string input_file);
        ~cCodeGen();

        virtual void VisitAllNodes(cAstNode *node);
        void OutputcFuncDeclNode(cFuncDeclNode *node);

        virtual void Visit(cProgramNode *node);
        virtual void Visit(cBlockNode *node);
        virtual void Visit(cPrintNode *node);
        virtual void Visit(cIntExprNode *node);
        virtual void Visit(cBinaryExprNode *node);
        virtual void Visit(cOpNode *node);
        virtual void Visit(cAssignNode *node);
        virtual void Visit(cVarExprNode *node);
        virtual void Visit(cIfNode *node);
        virtual void Visit(cWhileNode *node);
        virtual void Visit(cFuncDeclNode *node);
        virtual void Visit(cFuncExprNode *node);
        virtual void Visit(cParamListNode *node);
};