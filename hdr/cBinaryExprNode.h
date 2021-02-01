#pragma once
//**************************************
// cBinaryExprNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 1, 2021
//

#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        cBinaryExprNode(cExprNode *left, int op, cExprNode *right) : cExprNode()
        {
            AddChild(left);
            AddChild(new cOpNode(op));
            AddChild(right);
        }

        cExprNode* GetLeft()
        {
            return static_cast<cExprNode*>(GetChild(0));
        }

        cExprNode* GetRight()
        {
            return static_cast<cExprNode*>(GetChild(2));
        }
        
        cOpNode* GetOp()
        {
            return static_cast<cOpNode*>(GetChild(1));
        }
        
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};