#pragma once
//**************************************
// cVarDeclNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 1, 2021
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"
#include "lex.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol *type, cSymbol *name)
        {
            AddChild(type);

            if (!g_symbolTable->FindLocal(name->GetName()))
            {
                cSymbol *toInsert = name;

                // Exists in parent scope
                if (g_symbolTable->Find(name->GetName()))
                {
                    toInsert = new cSymbol(name->GetName());
                }

                g_symbolTable->Insert(toInsert);

                toInsert->SetDecl(this);
                AddChild(toInsert);
            }
            else
            {
                std::string error = "Symbol ";
                error += name->GetName();
                error += " already defined in current scope";
                SemanticError(error);
            }
        }

        virtual cDeclNode *GetType()
        {
            return this->GetTypeSymbol()->GetDecl();
        }

        cSymbol* GetTypeSymbol()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};