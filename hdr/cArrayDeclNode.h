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
        cArrayDeclNode(cSymbol *type, cSymbol *name, int size) : cDeclNode()
        {
            m_size = size;

            AddChild(type);
            AddChild(name);

            g_symbolTable->Insert(name);
        }

        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString()
        {
            return " count=\"" + std::to_string(m_count) + "\"";
        }

protected:
        int m_size;
};