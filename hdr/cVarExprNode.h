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

        void InsertSymbol(cSymbol *name)
        {
            cDeclNode *type = nullptr;
            if (this->NumElements() == 0)
            {
                type = this->GetBaseType();
            }
            else
            {
                type = this->GetType();
            }

            if (type == nullptr || !type->IsStruct())
            {
                std::string error = this->GetFullName();
                error += " is not a struct";
                SemanticError(error);
            }
            else
            {
                cStructDeclNode *structDecl = static_cast<cStructDeclNode*>(type);
                cSymbol *member = structDecl->GetMember(name->GetName());
                if (member == nullptr)
                {
                    std::string error = name->GetName();
                    error += " is not a field of ";
                    error += this->GetFullName();
                    SemanticError(error);
                }
                else
                {
                    name->SetDecl(member->GetDecl());
                }
            }

            AddChild(name);
        }

        void InsertExpr(cExprNode *index)
        {
            AddChild(index);
        }

        cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        virtual cDeclNode *GetBaseType()
        {
            cSymbol *name = this->GetName();
            cDeclNode *varDecl = name->GetDecl();
            if (varDecl != nullptr)
            {
                return varDecl->GetType();
            }

            return nullptr;
        }

        virtual cDeclNode *GetType()
        {
            cSymbol *last = GetElement(NumElements() - 1);
            if (last != nullptr)
            {
                cDeclNode *decl = last->GetDecl();
                if (decl != nullptr)
                {
                    return decl->GetType();
                }
            }

            return nullptr;
        }

        std::string GetFullName()
        {
            cDeclNode *base = this->GetBaseType();
            std::string name = this->GetName()->GetName();
            if (base->IsStruct())
            {
                for (int i = 0; i < this->NumElements(); i++)
                {
                    name += "." + GetElement(i)->GetName();
                }
            }

            return name;
        }

        cSymbol* GetElement(int i)
        {
            return static_cast<cSymbol*>(GetChild(i + 1));
        }

        int NumElements()
        {
            return NumChildren() - 1;
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};