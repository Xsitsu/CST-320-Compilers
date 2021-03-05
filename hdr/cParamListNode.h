#pragma once
//**************************************
// cParamListNode.h
//
// Author: Jacob Locke
//
// Date: Feb. 10, 2021
//

#include "cAstNode.h"
#include "cExprNode.h"

class cParamListNode : public cAstNode
{
public:
    cParamListNode(cExprNode *param) m_size(0) : cAstNode()
    {
        AddChild(param);
    }
    
    void Insert(cExprNode *param)
    {
        AddChild(param);
    }

    int NumParams()
    {
        return NumChildren();
    }

    cExprNode* GetParam(int i)
    {
        return static_cast<cExprNode*>(GetChild(i));
    }
    
    virtual string NodeType() { return string("params"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    int GetSize() { return this->m_size; }
    void SetSize(int size) { this->m_size = size; }

    virtual string AttributesToString()
    {
        if (this->m_size == 0) return "";

        string result(" size=\"");
        result += std::to_string(this->m_size) + "\"";
        return result;
    }

protected:
    int m_size;
};