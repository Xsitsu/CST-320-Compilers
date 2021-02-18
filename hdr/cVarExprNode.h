#pragma once
//**************************************
// cVarExprNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 1, 2021
//

#include "cSymbol.h"
#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol *name) : cExprNode()
        {
            AddChild(name);
        }

        void Insert(cSymbol *name)
        {
            AddChild(name);
        }

        void Insert(cExprNode *index)
        {
            AddChild(index);
        }

        cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        virtual cDeclNode *GetType()
        {
            cSymbol *name = this->GetName();
            cDeclNode *varDecl = name->GetDecl();
            if (varDecl != nullptr)
            {
                return varDecl->GetType()->GetDecl();
            }

            return nullptr;
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};