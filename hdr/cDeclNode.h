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

        virtual cDeclNode *GetType() = 0;

        virtual bool IsNumber() { return this->IsChar() || this->IsInt || this->IsFloat() }
        virtual bool IsChar() { return false; }
        virtual bool IsInt() { return false; }
        virtual bool IsFloat() { return false; }

};
