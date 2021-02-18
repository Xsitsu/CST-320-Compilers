#pragma once
//**************************************
// cBaseTypeNode
//
// Author: Jacob Locke
//
// Date: Feb. 17, 2021
//

#include "cDeclNode.h"
#include "cSymbolTable.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        cBaseTypeNode(string name, int size, bool isFloat) : cDeclNode() 
        {
            m_name = name;
            m_size = size;
            m_isFloat = isFloat;
        }

        bool IsFloat() { return m_isFloat; }
        bool IsInt()   { return (!m_isFloat) && (m_size>1); }
        bool IsChar()  { return (!m_isFloat && m_size==1); }

        virtual string NodeType() { return "base_type"; }

        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        std::string m_name;
        int m_size;
        bool m_isFloat;
};