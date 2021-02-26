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

            if (!g_symbolTable->Find(name->GetName()))
            {
                std::string error = "Symbol ";
                error += name->GetName();
                error += " not defined";
                SemanticError(error);
            }
        }

        void Insert(cSymbol *name)
        {
            AddChild(name);
        }

        void Insert(cExprNode *index)
        {
            AddChild(index);
        }

        void StructIndex(cVarExprNode *index)
        {
            if (!this->GetName()->GetDecl()->IsStruct())
            {
                std::string error = this->GetName()->GetName();
                error += " is not a struct";
                SemanticError(error);
            }

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
                return varDecl->GetType();
            }

            return nullptr;
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};