#pragma once
//**************************************
// cProgramNode.h
//
// Defines AST node for a lang program
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cBlockNode.h"

class cProgramNode : public cAstNode
{
    public:
        // param is the block that makes up the program
        cProgramNode(cBlockNode *block) : cAstNode()
        {
            AddChild(block);
        }

        virtual string NodeType() { return string("program"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        cBlockNode* GetBlock()
        {
            return static_cast<cBlockNode*>(GetChild(0));
        }

        virtual string AttributesToString()
        {
            if (this->m_size > 0)
            {
                return " size=\"" + std::to_string(this->m_size) + "\"";
            }
            return "";
        }
};
