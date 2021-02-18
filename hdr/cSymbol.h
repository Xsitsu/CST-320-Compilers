#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "cAstNode.h"

class cSymbol : public cAstNode
{
    public:
        // param is name of symbol
        cSymbol(string name);

        // return name of symbol
        string GetName();
        bool IsType();
        void SetIsType(bool val);

        void SetDecl(cDeclNode *decl);
        cDeclNode* GetDecl();

        virtual string AttributesToString();
        virtual string NodeType();
        virtual void Visit(cVisitor *visitor);
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        bool m_isType;
        cDeclNode *m_decl;
};
