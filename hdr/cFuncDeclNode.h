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
        cFuncDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {
            AddChild(type);
            AddChild(name);

            g_symbolTable->Insert(name);
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

        virtual cDeclNode* GetType()
        {
            return static_cast<cSymbol*>(GetChild(0))->GetDecl(); 
        }

        virtual cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(1));
        }
};