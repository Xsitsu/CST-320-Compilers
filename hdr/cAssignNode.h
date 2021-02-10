#pragma once
//**************************************
// cAssignNode.h
//
// Author: Jacob Locke
//
// Date: Jan. 10, 2021
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        cAssignNode(cVarExprNode *lval, cExprNode *rval) : cStmtNode()
        {
            AddChild(lval);
            AddChild(rval);
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};