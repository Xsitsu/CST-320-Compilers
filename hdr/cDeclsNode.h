#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode()
        {
            AddChild(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        cDeclNode* GetDecl(int index)
        {
            return static_cast<cDeclNode*>(GetChild(index));
        }

        int NumDecls()
        {
            return this->NumChildren();
        }

        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        virtual string AttributesToString()
        {
            if (this->m_size > 0)
            {
                return " size=\"" + std::to_string(this->m_size) + "\"";
            }
            return "";
        }

        int GetSize() { return m_size; }
        void SetSize(int size) { m_size = size; }

    protected:
        int m_size;
};
