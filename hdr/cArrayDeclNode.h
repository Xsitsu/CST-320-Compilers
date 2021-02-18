#pragma once
//**************************************
// cArrayDeclNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

#include "lex.h"

class cArrayDeclNode : public cDeclNode
{
    public:
        cArrayDeclNode(cSymbol *type, cSymbol *inName, int size) : cDeclNode()
        {
            cSymbol *name;

            m_size = size;

            AddChild(type);

            name = g_symbolTable->FindLocal(inName->GetName());
            if (name == nullptr)
            {
                name = inName;

                if (g_symbolTable->Find(inName->GetName()) != nullptr)
                {
                    name = new cSymbol(inName->GetName());
                }

                g_symbolTable->Insert(name);
            }

            name->SetIsType(true);
            AddChild(name);
        }

        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString()
        {
            return " count=\"" + std::to_string(m_size) + "\"";
        }

        virtual cDeclNode* GetType() { return this; }

protected:
        int m_size;
};