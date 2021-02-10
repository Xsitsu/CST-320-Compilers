#pragma once
//**************************************
// cIfNode.h
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cStmtNode.h"

class cIfNode : public cStmtNode
{
    public:
        cIfNode(cExprNode *condition, cStmtsNode *stmt, cStmtsNode *elseStmt)
        {
            AddChild(condition);
            AddChild(stmt);
            AddChild(elseStmt);
        }

        virtual string NodeType() { return string("if"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};