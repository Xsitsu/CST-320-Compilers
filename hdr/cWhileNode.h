#pragma once
//**************************************
// cWhileNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cWhileNode : public cStmtNode
{
    public:
        cWhileNode(cExprNode *condition, cStmtNode *stmt) : cStmtNode()
        {
            AddChild(condition);
            AddChild(stmt);
        }

        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        cExprNode* GetExpr()
        {
            return static_cast<cExprNode*>(GetChild(0));
        }

        cStmtNode* GetStmt()
        {
            return static_cast<cStmtNode*>(GetChild(1));
        }
};