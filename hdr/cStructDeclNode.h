#pragma once
//**************************************
// cStructDeclNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

#include "lex.h"

class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(symbolTable_t *symTable, cDeclsNode *decls, cSymbol *structName) : cDeclNode()
        {
            cSymbol *name;

            AddChild(decls);

            name = g_symbolTable->FindLocal(structName->GetName());
            if (name == nullptr)
            {
                name = structName;

                if (g_symbolTable->Find(structName->GetName()) != nullptr)
                {
                    name = new cSymbol(structName->GetName());
                }

                g_symbolTable->Insert(name);
            }

            name->SetIsType(true);
            name->SetDecl(this);
            AddChild(name);

            m_symTable = symTable;
        }

        virtual bool IsStruct() { return true; }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual cDeclNode* GetType() { return this; }

        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }

        bool HasMember(std::string name)
        {
            return (this->GetMember(name) != nullptr);
        }

        cSymbol* GetMember(std::string name)
        {
            auto found = m_symTable->Find(name);
            if (found != m_symTable->end())
            {
                return found->second;
            }
            return nullptr;
        }

    protected:
        symbolTable_t *m_symTable;
};