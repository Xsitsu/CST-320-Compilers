#pragma once
//**************************************
// cParamsNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cParamsNode : public cDeclsNode
{
    public:
        cParamsNode(cDeclNode *decl) : cDeclsNode(decl) {}

        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};