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
        
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

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

        virtual cDeclNode *GetType()
        {
            cDeclNode *left;
            cDeclNode *right;

            left = GetLeft()->GetType();
            right = GetRight()->GetType();

            if (left == nullptr || right == nullptr)
            {
                return nullptr;
            }

            if (!left->IsNumber() || !right->IsNumber())
            {
                // TODO: Semantic error
                return nullptr;
            }

            if (left == right) return left;
            if (left->IsFloat()) return left;
            if (right->IsFloat()) return right;
            if (left->IsInt()) return left;
            if (right->IsInt()) return right;

            // Shouldn't happen
            return nullptr;
        }
};
