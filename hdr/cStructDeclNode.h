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

            name = g_SymbolTable.FindLocal(structName->GetName());
            if (name == nullptr)
            {
                name = structName;

                if (g_SymbolTable.Find(structName->GetName()) != nullptr)
                {
                    name = new cSymbol(structName->GetName());
                }

                g_SymbolTable.Insert(name);
            }

            AddChild(name);
        }

        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};