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

            if (lvalType != nullptr && rvalType != nullptr)
            {
                if (!lvalType->IsCompatible(rvalType))
                {
                    cSymbol *lvalSym = nullptr;
                    cSymbol *rvalSym = nullptr;

                    if (lvalType != nullptr) lvalSym = lvalType->GetName();
                    if (rvalType != nullptr) rvalSym = rvalType->GetName();

                    std::string error = "Cannot assign ";
                    if (rvalSym != nullptr) error += rvalSym->GetName();
                    else error += "_NO_SYMBOL_";
                    error += " to ";
                    if (lvalSym != nullptr) error += lvalSym->GetName();
                    else error += "_NO_SYMBOL_";
                    SemanticError(error);
                }
            }
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};