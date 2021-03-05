#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}

        virtual cDeclNode* GetBaseType() { return GetType(); }
        virtual cDeclNode *GetType() = 0;
        virtual cSymbol *GetName() = 0;

        virtual bool IsFunc() { return false; }
        virtual bool IsStruct() { return false; }

        virtual bool IsNumber() { return this->IsChar() || this->IsInt() || this->IsFloat(); }
        virtual bool IsChar() { return false; }
        virtual bool IsInt() { return false; }
        virtual bool IsFloat() { return false; }

        bool IsCompatible(cDeclNode *other)
        {
            if (other == nullptr) return false;
            if (this == other) return true;
            if (this->IsFloat()) return true;
            if (this->IsInt() && other->IsChar()) return true;

            return false;
        }

        int GetSize() { return this->m_size; }
        void SetSize(int size) { this->m_size = size; }
        int GetOffset() { return this->m_offset; }
        void SetOffset(int offset) { this->m_offset = offset; }

        virtual string AttributesToString()
        {
            if (this->m_size > 0)
            {
                return " size=\"" + std::to_string(this->m_size) + "\" \
                offset=\"" + std::to_string(this->m_offset) + "\"";;
            }
            return "";
        }

    protected:
        int m_size;
        int m_offset;

};
