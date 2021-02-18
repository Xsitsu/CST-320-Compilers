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

            cDeclNode *lvalType = lval->GetType();
            cDeclNode *rvalType = rval->GetType();

            if (lvalType == nullptr || !lvalType->IsCompatible(rvalType))
            {
                std::string error = "Cannot assign ";
                error += rvalType->GetName()->GetName();
                error += " to ";
                error += lvalType->GetName()->GetName();
                SemanticError(error);
            }
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};