#pragma once
//**************************************
// cParamListNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cExprNode.h"

class cParamListNode : public cAstNode
{
public:
    cParamListNode(cExprNode *param) : cAstNode()
    {
        AddChild(param);
    }
    
    void Insert(cExprNode *param)
    {
        AddChild(param);
    }

    int NumParams()
    {
        return NumChildren();
    }
    
    virtual string NodeType() { return string("params"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};