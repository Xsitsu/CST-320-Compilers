#pragma once
//**************************************
// cFuncDeclNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cStmtsNode.h"
#include "cDeclsNode.h"
#include "cDeclNode.h"

#include "lex.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol *type, cSymbol *inName) : cDeclNode()
        {
            cSymbol *name;

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

        void AddParams(cDeclsNode *params)
        {
            AddChild(params);
        }

        void AddDecls(cDeclsNode *decls)
        {
            AddChild(decls);
        }

        void AddStmts(cStmtsNode *stmts)
        {
            AddChild(stmts);
        }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};