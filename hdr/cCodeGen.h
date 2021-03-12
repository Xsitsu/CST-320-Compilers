#pragma once

#include <string>

#include "cVisitor.h"

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(const std::string input_file);
        ~cCodeGen();

        virtual void VisitAllNodes(cAstNode *node);

        virtual void Visit(cProgramNode *node);
        virtual void Visit(cBlockNode *node);
        virtual void Visit(cPrintNode *node);
        virtual void Visit(cIntExprNode *node);
};